# Learnings, walkthrough and benchmarks from setting up local LLMs

***Currently running everything on CM5, would like to move the web interface at least to a spare RPi 4B***

## Agents

1. [AIDER](https://aider.chat) A local terminal interface. I prefer OLLAMA local anyway and this can't be accesses remotely so won't be recorded in any of the benchmark results.

2. [OLLAMA](https://ollama.com) Out-of-the-box experience. Some modifications made to the configuration:

```
sudo systemctl edit ollama.service
```
added in these lines to make the API vieable from the web and control RAM usage:

```
[Service]
Environment="OLLAMA_HOST=0.0.0.0"
Environment="OLLAMA_CONTEXT_LENGTH=4096"
Environment="OLLAMA_NUM_PARALLEL=1"
```
then restart the ollama service:
```
sudo systemctl daemon-reload
sudo systemctl restart ollama
```

3. [llama.cpp]([https://llama.app](https://github.com/ggml-org/llama.cpp))

...

## Web Interface

1. [Open WebUI](https://openwebui.com) Out-of-the-box experience using docker to host the web UI:

```
docker run -d -p 3000:8080 --add-host=host.docker.internal:host-gateway -v open-webui:/app/backend/data --name open-webui --restart always ghcr.io/open-webui/open-webui:main
```
nice it has all the LLMs to choose from the API as it is running.

2. [llama.cpp-server](https://github.com/ggml-org/llama.cpp) Built the application from source on the SBC to hopefully use less overhead and be more efficient.

```
llama-server -hf Qwen/Qwen2.5-Coder-3B-Instruct-GGUF:q4_k_m --host 0.0.0.0
```
I have to launch the models individually. To download and launch with the other models:
```
wget https://huggingface.co/Qwen/Qwen2.5-Coder-3B-Instruct-GGUF/resolve/main/qwen2.5-coder-3b-instruct-q4_k_m.gguf -O qwen2.5-coder-3b-q4km.gguf
wget https://huggingface.co/bartowski/Llama-3.2-3B-Instruct-GGUF/resolve/main/Llama-3.2-3B-Instruct-Q4_K_M.gguf -O llama32-3b-q4km.gguf
```
...
```
llama-server -m models/qwen2.5-coder-3b-q4km.gguf --host 0.0.0.0
llama-server -m models/llama32-3b-q4km.gguf --host 0.0.0.0 --ctx-size 4096
```
...
## LLMs

These are the LLMs I will be testing with, they are smaller LLMs confimed to work within the Pi CM5 8GB RAM limit.

 1. ministral-3:3b
 2. llama3.2:3b
 3. qwen2.5-coder:3b

## Results

prompt test 1: "write an itinerary for a weekend in Bath"

prompt test 2: "write a template gitlab ci/cd .yaml for me to use for building, testing, and deploying"

prompt test 3: "write a c function for reversing a string"

### Overview of llms under test

|LLM|Local Size|
|---|---|
|ministral-3:3b|3.0 GB|
|llama3.2:3b|2.0 GB|  
|qwen2.5-coder:3b|1.9 GB|

### Speed test results

|Test|ministral-3:3b|llama3.2:3b|qwen2.5-coder:3b|
|---|---|---|---|
|Open web/ollama prompt test 1|2.19 t/s | | |
|Open web/ollama prompt test 2| | | |
|Open web/ollama prompt test 3| | | |
|llama.cpp web prompt test 1| |4.34 t/s|4.61 t/s|
|llama.cpp web prompt test 2| |4.19 t/s|4.58 t/s|
|llama.cpp web prompt test 3| |4.42 t/s|4.71 t/s|
|RAM usage*| |3.1GB|3.6GB|
|llama.cpp context| |limited to 4096|32.77K|

*just quickly taked with the `free -h` command, so will include everything else running on the RPI but I will make sure to restart after each test.

### notes

accuracy, continued conversation, etc.

 - ministral on ollama: about 4 mins to start up, very thorough itinerary about 12 mins total though.

 - llama32 on llama.cpp: required context limiting to get it to run. Good weekend itinerary, created a whole advanced template for 2nd primpt (using up context). c code looks good.

 - Qwen on llama.cpp: went up to 5 days on weekend prompt on llama.cpp, maybe confused. Handled the others well, instant feedback, templace and C code look good.

So ollama takes considerably longer, it has to spool up the AI each time, but you are able to easily switch between the LLMs if needed. Similar interface between both, don't really have a preference. Llama.cpp is much better if you know what LLM you want to use.

