# Learnings, walkthrough and benchmarks from setting up local LLMs

***Currently running everything on CM5, would like to move the web interface at least to a spare RPi 4B***

## Agents:

[AIDER](https://aider.chat) A local terminal interface. I prefer OLLAMA local anyway and this can't be accesses remotely so won't be recorded in any of the benchmark results.

[OLLAMA](https://ollama.com) Out-of-the-box experience. Some modifications made to the configuration:

```
sudo systemctl edit ollama.service
```
added in these lines to make the API vieable from the web and control RAM usage:

...

```
sudo systemctl daemon-reload
sudo systemctl restart ollama
```

[llama.cpp](https://llama.app)

...

## Web Interface:

[Open WebUI](https://openwebui.com) Out-of-the-box experience using docker to host the web UI 

```
docker run -d -p 3000:8080 --add-host=host.docker.internal:host-gateway -v open-webui:/app/backend/data --name open-webui --restart always ghcr.io/open-webui/open-webui:main
```

llama.cpp serve

## LLMs:

These are the LLMs I will be testing with, they are smaller LLMs confimed to work within the Pi CM5 8GB RAM limit.

 - ministral-3:3b
 - llama3.2:3b
 - qwen2.5-coder:3b

## Results:
|LLM|Local Size|
|---|---|
|ministral-3:3b|3.0 GB| 
|llama3.2:3b|2.0 GB|    
|qwen2.5-coder:3b|1.9 GB|
