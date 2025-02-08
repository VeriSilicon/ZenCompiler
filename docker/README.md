# Build docker image
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
