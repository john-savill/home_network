# Contents

Agent config

Web UI config

LLMs under test

Test setup

Test quantifiable results

Test notes

# Learnings, walkthrough and benchmarks from setting up local LLMs

***Currently running everything on CM5, would like to move the web interface at least to a spare RPi 4B***

## Agents

1. [AIDER](https://aider.chat) A local terminal interface. I prefer OLLAMA local anyway and this can't be accessed remotely so won't be recorded in any of the benchmark results.

2. [OLLAMA](https://ollama.com) Out-of-the-box experience `curl -fsSL https://ollama.com/install.sh | sh`. Some modifications made to the configuration:

```
sudo systemctl edit ollama.service
```
added in these lines to make the API viewable from the web and control RAM usage:

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
To run a specific model from hugging face I just ran it once locally to download it into the local cache. The LLM can then be tested locally or used from the OpenWeb UI when pointed at the ollama public API:

```
ollama run qwen2.5-coder:3b
ollama run llama3.2:3b
ollama run ministral-3:3b
```
***Note: These are the only models I tested with OLLAMAa***

3. [llama.cpp]([https://llama.app](https://github.com/ggml-org/llama.cpp))

I built this from source on the Pi CM5 so that it is optimised. The process was relatively simple, following the build steps from the repo. I did finish with adding `export PATH="/home/john/llama.cpp/build/bin:$PATH"` to the end of the .bashrc file, which isn't detailed in the setup but required to run the commands outside of a the build/bin folder.

## Web Interface

1. [Open WebUI](https://openwebui.com) Out-of-the-box experience using docker to host the web UI of OLLAMA:

```
docker run -d -p 3000:8080 --add-host=host.docker.internal:host-gateway -v open-webui:/app/backend/data --name open-webui --restart always ghcr.io/open-webui/open-webui:main
```
nice it has all the LLMs to choose from the API as it is running. Has user login page. On my network can be found at `http://192.168.0.21:3000/` and using the 11434 endpoint `http://192.168.0.21:11434` you can review that the backend is active should the webUI go down. 

2. [llama.cpp-server](https://github.com/ggml-org/llama.cpp) Built the application from source on the SBC to hopefully use less overhead and be more efficient.

```
llama-server -hf Qwen/Qwen2.5-Coder-3B-Instruct-GGUF:q4_k_m --host 0.0.0.0
```
I am launching the models individually. To download:
```
wget https://huggingface.co/Qwen/Qwen2.5-Coder-3B-Instruct-GGUF/resolve/main/qwen2.5-coder-3b-instruct-q4_k_m.gguf -O qwen2.5-coder-3b-q4km.gguf
wget https://huggingface.co/bartowski/Llama-3.2-3B-Instruct-GGUF/resolve/main/Llama-3.2-3B-Instruct-Q4_K_M.gguf -O llama32-3b-q4km.gguf
wget https://huggingface.co/unsloth/Ministral-3-3B-Instruct-2512-GGUF/resolve/main/Ministral-3-3B-Instruct-2512-Q4_K_M.gguf -O Ministral-3-3B-q4km.gguf
wget https://huggingface.co/unsloth/Qwen3.5-2B-GGUF/resolve/main/Qwen3.5-2B-Q4_K_M.gguf -O qwen3.5-2b-q4km.gguf
```
and then launch the models, examples are below:
```
llama-server -m models/qwen2.5-coder-3b-q4km.gguf --host 0.0.0.0
llama-server -m models/llama32-3b-q4km.gguf --host 0.0.0.0 --ctx-size 4096
```
You can also just launch the web interface and select, load, and unload models which is very convenient. The command is (provided the models are puled to the right location:
```
llama-server --models-dir models/ --host 0.0.0.0
```
For launching with a specific configuration to set context limits I have used a [models.ini](models.ini) file. Launch with:
```
llama-server --models-preset models.ini --host 0.0.0.0
```

## LLMs

These are the LLMs I will be testing with, they are smaller LLMs confimed to work within the Pi CM5 8GB RAM limit. I will also try to test them with different variables i.e. modifying their conext token amount.  

 1. ministral-3:3b
 2. llama-3.2:3b
 3. qwen-2.5-coder:3b
 4. qwen-3.5:2b
 5. qwen-3.5:4b
 6. gemma-4:E2b

There are a few others I would like to test on Raspberry Pi. I will note them here for future reference:
 1. [phi 4 mini from microsoft](https://huggingface.co/microsoft/Phi-4-mini-instruct)

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
|qwen3.5:2b|1.19GB|

***Unfinished, will add the detials of the other LLM I have testeds**

### Speed test results

|Test|ministral-3:3b|llama3.2:3b|qwen2.5-coder:3b|qwen3.5:2b|
|---|---|---|---|---|
|Open web/ollama prompt test 1|2.19 t/s| | | |
|Open web/ollama prompt test 2|2.08 t/s| | | |
|Open web/ollama prompt test 3| | | | |
|Open web/ollama RAM usag*|5.2GB| | | |
|llama.cpp web prompt test 1|3.30 t/s|4.34 t/s|4.61 t/s|5.93 t/s|
|llama.cpp web prompt test 2|3.10 t/s|4.19 t/s|4.58 t/s|5.88 t/s|
|llama.cpp web prompt test 3|3.78 t/s |4.42 t/s|4.71 t/s|6.03 t/s|
|llama.cpp RAM usage*|3.1GB|3.1GB|3.6GB|4.9GB|
|llama.cpp context|limited to 4k**|limited to 4k**|32.77K|262.14k|

*just quickly taken with the `free -h` command, so will include everything else running on the RPI but I will make sure to restart after each test.
**limited to just 4k to get running, it will run with larger contexts, I will check the imact this has on speed.

### notes

clearing buffer cache command that's useful when switching between models a lot: `sync && echo 1 | sudo tee /proc/sys/vm/drop_caches`

accuracy, continued conversation, other tools (image rec, image creation?) etc.

Outputs from the prompts can be found in the [ai_code_results](ai_code_results/) directory.

 - ministral on ollama: **Context limiting from ollama config** about 4 mins to start up, very thorough itinerary about 12 mins total though. Yaml very detailed again over 12 mins total, very slow.
 - ministral on llama.cpp: **required context limiting to run.** Noticably slower ininerary but detailed and kept to 2 days but used up over a third of it's context cache. Same happened with the .yaml prompt, very detailed. Speed seems to tail off the longer the prompt is working for.

 - llama32 on llama.cpp: **required context limiting to get it to run.** Good weekend itinerary, created a whole advanced template for 2nd primpt (using up context). c code looks good.

 - Qwen 2.5 on llama.cpp: went up to 5 days on weekend prompt on llama.cpp, maybe confused. Handled the others well, instant feedback, templace and C code look good, will have to test.

 - Qwen 3.5:2b on llama.cpp: again longer weekend prompt, better explanations I think around the response itself. much quicker, still lacking some detail compared to llama32 and ministral, and will ahve to check accuracy.

So ollama takes considerably longer (maybe up to 10x), it has to spool up the AI each time, but you are able to easily switch between the LLMs if needed. Similar interface between both, don't really have a preference. Llama.cpp is much better if you know what LLM you want to use.

I have been having my doubts about Qwen, I think some of the other LLMs are giving me more accurate results.

