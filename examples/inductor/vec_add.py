import torch
import triton

import vpex

if __name__ == "__main__":
    torch.manual_seed(0)
    device = torch.device("vsi")

    if device.type == "vsi":
        from triton.backends.vsi.driver import VSIDriver
        from triton.runtime import driver as triton_driver
        triton_driver.set_active(VSIDriver())

    x = torch.randn(
        size=(256,),
        dtype=torch.float16,
        device=device
    )
    y = torch.randn(
        size=(256,),
        dtype=torch.float16,
        device=device
    )

    @torch.no_grad()
    def vec_add(lhs: torch.Tensor, rhs: torch.Tensor) -> torch.Tensor:
        out = lhs + rhs
        return out

    with torch.inference_mode():
        out_golden: torch.Tensor = vec_add(x, y)

    # Inductor triton options.
    torch._inductor.config.triton.codegen_upcast_to_fp32 = False

    model_compiled = torch.compile(
        vec_add,
        dynamic=False,
        fullgraph=True,
        backend="inductor"
    )
    with torch.inference_mode():
        out_inductor: torch.Tensor = model_compiled(x, y)
        max_diff = torch.max(torch.abs(out_inductor - out_golden)).item()
        print(
            f"output shape: {tuple(out_inductor.shape)}, max diff: {max_diff:.2e}")
        torch.testing.assert_close(out_inductor.cpu(), out_golden.cpu())
