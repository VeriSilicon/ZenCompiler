# TorchInductor Integration

## Setup

### PyTorch

To use with TorchInductor, you need to use the `triton-vsi-backend` branch of our [Forked PyTorch](https://github.com/VeriSilicon/pytorch/tree/triton-vsi-backend).

This branch is based on upstream `v2.5.1` version and has only python source modifications, you can either build a PyTorch from source:

```shell
git clone --recurse-submodules --shallow-submodule --depth=1 --branch="triton-vsi-backend" https://github.com/VeriSilicon/pytorch.git
cd pytorch
PYTORCH_BUILD_VERSION="2.5.1" PYTORCH_BUILD_NUMBER=1 _GLIBCXX_USE_CXX11_ABI=0 BUILD_TEST=0 python3 setup.py install
```

or make patches and apply to the python source of upstream `v2.5.1` python package:

```shell
git clone --depth=10 --branch="triton-vsi-backend" https://github.com/VeriSilicon/pytorch.git
cd pytorch
git format-patch 'a8d6afb511a69687bbb2b7e88a3cf67917e1697e'
# Now you get several patch files.

pip3 install torch==2.5.1
pip3 show torch
cd <your_env/lib/python3.x/site-packages>
patch -p1 < ${patch_file} # Apply patch one-by-one.
```

### Triton Backend Plugin

See [triton-vsi-backend](https://github.com/VeriSilicon/triton-vsi-backend)
