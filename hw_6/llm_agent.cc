#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

std::string api_key = std::getenv("OPENAI_API_KEY") ?: "";
const std::string API_URL = "https://api.openai.com/v1/chat/completions";

using json = nlohmann::json;

json add(double a, double b) {return json::array({"result", a + b});}
json sub(double a, double b) {return json::array({"result", a - b});}
json mult(double a, double b) {return json::array({"result", a * b});}
json divide(double a, double b) {return json::array({"result",a / b});}
json exps(double a, int b) {return json::array({"result", pow(a,b)});}
json mod(int a, int b) {return json::array({"result", a % b});}
json mean(std::vector<double> a) {
    double sum = 0.0;
    for(size_t i = 0; i < a.size(); i++)
        sum += a[i];

    return json::array({"result", sum/a.size()});
}

double median(std::vector<double> a) {
    std::sort (a.begin(), a.end());
    if(a.size() % 2)
        return a[a.size()/2] + a[a.size()/2-1];
        //return json::array({"result", a[a.size()/2] + a[a.size()/2-1]});
    else
        return a[a.size()/2];
        //return json::array({"result", a[a.size()/2]});
}

// How much numbers deviate from mean: sqrt(sum(pow(n_i - mean()),2)/n))
double standardDev(std::vector<double> a) {
    double means = mean(a)[1].get<double>(), sum = 0.0;
    int n = a.size();

    for(size_t i = 0; i < n; i++)
        sum += pow(a[i] - means, 2);

    return sqrt(sum/n);
}

class CurlHandler {
private:
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
        userp->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

public:
    static std::string makeRequest(const std::string& url, const json& payload, const std::string& api_key) {
        CURL* curl = curl_easy_init();
        if (!curl) throw std::runtime_error("Failed to initialize CURL");

        std::string readBuffer;
        std::string auth_header = "Authorization: Bearer " + api_key;
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, auth_header.c_str());

        std::string payload_str = payload.dump();
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload_str.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
            throw std::runtime_error(std::string("CURL error: ") + curl_easy_strerror(res));
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        return readBuffer;
    }
};

// Generate n many numbers using Fibinnoci sequence.
int Fibb_gen(int nums_generated, std::vector<int> &fibseq){

    if(nums_generated == 0){
        // Search for number in fib sequence. If generated do not push to sequence
        auto it = std::find(fibseq.begin(), fibseq.end(), 0);

        if (it != fibseq.end()) {
            return 0;
        } else {
            fibseq.push_back(0);
            return 0;
        }
    }
    else if(nums_generated == 1){
        auto it = std::find(fibseq.begin(), fibseq.end(), 1);

        if (it != fibseq.end()) {
            return 1;
        } else {
            fibseq.push_back(1);
            return 1;
        }
    }else{
        int val = Fibb_gen(nums_generated-1, fibseq) + Fibb_gen(nums_generated-2, fibseq);
        auto it = std::find(fibseq.begin(), fibseq.end(), val);

        if (it != fibseq.end()) {
            return val;
        } else {
            fibseq.push_back(val);
            return val;
        }
    }
}

json get_tool_definition() {
    return json::array({
    {
        {"type", "function"},
        {"function", {
            {"name", "fibonacci"},
            {"description", "Generate numbers that are part of the Fibonacci sequence"},
            {"parameters", {
                {"type", "object"},
                {"properties", {
                    {"nums_generated", {
                        {"type", "integer"},
                        {"description", "How many Fibonacci numbers to generate"}
                    }}
                }},
                {"required", json::array({"nums_generated"})}
            }}
        }}
    },

    {
        {"type", "function"},
        {"function", {
            {"name", "mean"},
            {"description", "Compute the mean of the given numbers"},
            {"parameters", {
                {"type", "object"},
                {"properties", {
                    {"a", {
                        {"type", "array"},
                        {"items", {{"type", "number"}}},
                        {"description", "List of numbers"}
                    }}
                }},
                {"required", json::array({"a"})}
            }}
        }}
    },

    {
        {"type", "function"},
        {"function", {
            {"name", "median"},
            {"description", "Compute the median of the given numbers"},
            {"parameters", {
                {"type", "object"},
                {"properties", {
                    {"a", {
                        {"type", "array"},
                        {"items", {{"type", "number"}}},
                        {"description", "List of numbers"}
                    }}
                }},
                {"required", json::array({"a"})}
            }}
        }}
    },

    {
        {"type", "function"},
        {"function", {
            {"name", "standard_deviation"},
            {"description", "Compute the standard deviation of the given numbers"},
            {"parameters", {
                {"type", "object"},
                {"properties", {
                    {"a", {
                        {"type", "array"},
                        {"items", {{"type", "number"}}},
                        {"description", "List of numbers"}
                    }}
                }},
                {"required", json::array({"a"})}
            }}
        }}
    },

    {
        {"type", "function"},
        {"function", {
            {"name", "add"},
            {"description", "Adds two numbers"},
            {"parameters", {
                {"type", "object"},
                {"properties", {
                    {"a", {{"type", "number"}}},
                    {"b", {{"type", "number"}}}
                }},
                {"required", json::array({"a", "b"})}
            }}
        }}
    },

    {
        {"type", "function"},
        {"function", {
            {"name", "subtract"},
            {"description", "Subtracts two numbers"},
            {"parameters", {
                {"type", "object"},
                {"properties", {
                    {"a", {{"type", "number"}}},
                    {"b", {{"type", "number"}}}
                }},
                {"required", json::array({"a", "b"})}
            }}
        }}
    },

    {
        {"type", "function"},
        {"function", {
            {"name", "multiplication"},
            {"description", "Multiplies two numbers"},
            {"parameters", {
                {"type", "object"},
                {"properties", {
                    {"a", {{"type", "number"}}},
                    {"b", {{"type", "number"}}}
                }},
                {"required", json::array({"a", "b"})}
            }}
        }}
    },

    {
        {"type", "function"},
        {"function", {
            {"name", "division"},
            {"description", "Divides two numbers"},
            {"parameters", {
                {"type", "object"},
                {"properties", {
                    {"a", {{"type", "number"}}},
                    {"b", {{"type", "number"}}}
                }},
                {"required", json::array({"a", "b"})}
            }}
        }}
    },

    {
        {"type", "function"},
        {"function", {
            {"name", "exponentiation"},
            {"description", "Finds exponent of a to the power of b"},
            {"parameters", {
                {"type", "object"},
                {"properties", {
                    {"a", {{"type", "number"}}},
                    {"b", {{"type", "number"}}}
                }},
                {"required", json::array({"a", "b"})}
            }}
        }}
    },

    {
        {"type", "function"},
        {"function", {
            {"name", "modulo"},
            {"description", "Finds the modulus of a divided by b"},
            {"parameters", {
                {"type", "object"},
                {"properties", {
                    {"a", {{"type", "integer"}}},
                    {"b", {{"type", "integer"}}}
                }},
                {"required", json::array({"a", "b"})}
            }}
        }}
    }

});
}

// Generate request schema from question. References messages to store request/response history.
json createResponse(std::string question, json &messages){
    std::string api_key = std::getenv("OPENAI_API_KEY") ?: "";

    if (api_key.empty()) {
        std::cerr << "Error: Set OPENAI_API_KEY environment variable" << std::endl;
        throw std::runtime_error("No OPENAI Key enviroment variable");
    }
    
    std::cout << "=== LLM Tool Calling Demo ===" << std::endl;
    
    // Create initial request to LLM
    messages.push_back({
        {"role", "user"}, {"content", question}}
    );

    json request = {
        {"model", "gpt-5-nano"},
        {"messages", messages},
        {"tools", get_tool_definition()},
        {"tool_choice", "required"}
    };

    return request;
}

void sendResponse(json request, json &messages){
    bool keep_running = true;

    // Continue querying request until model answers all statements.
    while (keep_running){
        std::cout << "\n[1] Sending query to LLM..." << std::endl;
        
        // Call API
        std::string response_str = CurlHandler::makeRequest(API_URL, request, api_key);
        json response = json::parse(response_str);
        
        std::cout << "[2] LLM responded" << std::endl;

        std::string finish_reason = response["choices"][0]["finish_reason"];

        std::cout << "finish_reason is " << finish_reason << std::endl;

        if(finish_reason == "tool_calls") {
            std::cout << "[3] LLM wants to use a tool!" << std::endl;

            json toolcall = response["choices"][0]["message"]["tool_calls"]; // Because we only have 1 tool call query 0
            std::cout << "[3.1] toolcall is: " << toolcall << std::endl;

            messages.push_back(response["choices"][0]["message"]);
            for(json tool : toolcall){

                std::string name = tool["function"]["name"];
                std::string id = tool["id"];

                json func = tool["function"];

                if (!func.contains("arguments") || func["arguments"].is_null()) {
                    throw std::runtime_error("Tool arguments missing or null");
                }

                json args = json::parse(func["arguments"].get<std::string>());

                std::vector<int> seq;
                json result;
                if(name == "fibonacci") {
                    Fibb_gen(args["nums_generated"], seq);
                    result = json::array({"result", seq});
                } else if (name == "mean") {
                    std::vector<double> a = args["a"];
                    result = json::array({"result", mean(a)});
                    //result = mean(a);
                } else if (name == "median") {
                    std::vector<double> a = args["a"];
                    result = median(a);
                } else if (name == "standard_deviation") {
                    std::vector<double> a = args["a"];
                    result = json::array({"result", standardDev(a)});
                    //result = standardDev(a);
                } else if (name == "multiplication"){
                    result = mult(args["a"], args["b"]);
                }

                std::cout << "[4] Tool executed. Result: " << result.dump() << std::endl;
                
                // Develop request and append request to messages.
                json assist_request = json::object({
                    {"role", "tool"},
                    {"type", "function_call_output"},
                    {"tool_call_id", tool["id"]},
                    {"content", result.dump()}}
                );
                messages.push_back(assist_request);
            }
            
            request = {
                {"model", "gpt-5-nano"},
                {"messages", messages},
                {"tools", get_tool_definition()}
            };

            std::cout << "\n[5] Sending response to LLM..." << std::endl;
            
        } else {
            // finish_reason is likely "stop"
            std::cout << "[6] Final Response: " << response["choices"][0]["message"]["content"] << std::endl;
            keep_running = false;
        }
    }
}

int main(){
    json messages;
    json request = createResponse("What's 2847 * 3921?", messages);
    sendResponse(request, messages);

    request = createResponse ("Find the mean and standard deviation of: 23, 45, 67, 12, 89, 34, 56, 78", messages);
    sendResponse(request, messages);

    request = createResponse ("Generate the first 20 Fibonacci numbers. Use numbers to then calculate their mean and median.", messages);
    sendResponse(request, messages);

    return 0;
}