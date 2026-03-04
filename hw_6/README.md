# ISSUES

Trying to run the llm_agent program and compile along side the random_process, stopwatch, and integrator was an issue. Because the elma image uses an outdated linux image debian 10 (buster) that is end of life its package mirrors were removed and doesn't allow for apt-get package manager usage. This prevented me from installing nolmann/json library to aid in Openai API calls.

When trying to install the json library within the eep520 image alongside elma as it could download packages, json conflicts begin with elma.

## Solution

The solution was to run elma and OpenAPI program in different containers. This required different linking options in the makefile. The only makefile differences were inclusion of -lelma and -lcurl.