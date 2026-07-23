# List of common commands used

## RPI configuration

clear cache
```
sync && echo 1 | sudo tee /proc/sys/vm/drop_caches
```
check memory usage
```
free -h
```

## models

download a model
```
wget ...
```

## llama.cpp 

launch server (models configureation needs to be written, host argument so it is viewable on network, tools for modifying local files)
```
llama-server --models-preset models.ini --host 0.0.0.0 --tools all
```

## OLLAMA

Ollama status check
```
sudo systemctl status ollama.service
```
Ollama service modify
```
sudo systemctl edit ollama.service
```

Ollama/daemon service restart
