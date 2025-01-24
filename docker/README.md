# Build docker image
Download VPEX from https://github.com/VeriSilicon/VPEX/releases/latest/download/vpex-*.whl into the docker/ directory at first.
``` bash
cd <current_dir>
docker build -t zen_compiler:latest .
```

# Or download from docker hub
``` bash
docker push mercurychen/zen_compiler:latest
```

# Run docker container
``` bash
docker run -d --name zenc zen_compiler:latest
docker exec -it zenc /bin/bash
```
