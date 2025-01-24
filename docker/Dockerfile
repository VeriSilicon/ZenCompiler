FROM ubuntu:22.04

# Update package lists and install basic utilities
RUN apt-get update && \
    apt-get install -y \
    lsb-release \
    software-properties-common \
    gnupg \
    wget \
    build-essential \
    cmake \
    git \
    vim \
    && rm -rf /var/lib/apt/lists/*

# Install LLVM 17
RUN wget https://apt.llvm.org/llvm.sh && \
    chmod +x llvm.sh && \
    ./llvm.sh 17 && \
    rm llvm.sh
# Update alternatives to use LLVM 17 by default
RUN update-alternatives --install /usr/bin/llvm-config llvm-config /usr/bin/llvm-config-17 100 && \
    update-alternatives --install /usr/bin/clang clang /usr/bin/clang-17 100 && \
    update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-17 100 && \
    update-alternatives --install /usr/bin/lld lld /usr/bin/lld-17 100

# Install Python and pip
RUN apt-get update && \
    apt-get install -y python3 python3-pip && \
    rm -rf /var/lib/apt/lists/*

# Install PyTorch CPU and Triton
RUN pip3 install --no-cache-dir torch==2.5.1 --index-url https://download.pytorch.org/whl/cpu && \
    pip3 install --no-cache-dir triton==3.1.0 pybind11 numpy -i https://mirrors.tuna.tsinghua.edu.cn/pypi/web/simple

# Set working directory
WORKDIR /wksp

# Clone FlagGems, trion-vsi-backend, ZenCompiler
RUN cd /wksp && \
    git clone --depth 1 https://github.com/VeriSilicon/FlagGems.git && \
    git clone --depth 1 https://github.com/VeriSilicon/triton-vsi-backend.git && \
    git clone --depth 1 https://github.com/VeriSilicon/ZenCompiler.git

# Copy ld_config.conf from host to /etc/ld.so.conf.d/ and update ldconfig
COPY ld_config.conf /etc/ld.so.conf.d/
RUN ldconfig

# link triton-vsi-backend to triton backends
RUN ln -s /wksp/triton-vsi-backend/backend /usr/local/lib/python3.10/dist-packages/triton/backends/vsi

# Copy VPEX wheel file from host and install it
# TODO: download from github releases https://github.com/VeriSilicon/VPEX
COPY vpex-*.whl /tmp/
RUN pip3 install /tmp/vpex-*.whl && rm /tmp/vpex-*.whl

# Keep container running
CMD ["tail", "-f", "/dev/null"]
