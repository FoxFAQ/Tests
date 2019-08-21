#include <string>

#include <grpcpp/grpcpp.h>
#include "math.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using math::Math;
using math::MathRequest;
using math::MathReply;

class MathClient
{
public:
    MathClient(std::shared_ptr<Channel> channel) : stub_(Math::NewStub(channel)) {}

    int sendRequest(int a, int b, int operation)
    {
        MathRequest request;

        request.set_a(a);
        request.set_b(b);
        request.set_operation(operation);

        MathReply reply;

        ClientContext context;

        Status status = stub_->sendRequest(&context, request, &reply);

        if(status.ok())
        {
            return reply.result();
        }
        else
        {
            std::cout << status.error_code() << ": " << status.error_message() << std::endl;
            return -1;
        }
    }

private:
    std::unique_ptr<Math::Stub> stub_;
};

void Run(int32_t a, int32_t b, int32_t operation)
{
    std::string address("0.0.0.0:30000");
    MathClient client(grpc::CreateChannel(address, grpc::InsecureChannelCredentials()));

    int response;

    response = client.sendRequest(a, b, operation);
    std::cout << "Result: " << response << std::endl;
}

int main(int argc, char* argv[])
{
std::cout << argv[3][0] << std::endl;
    if(argc == 4)
    {
        int32_t a = strtol(argv[1], NULL, 10);
        int32_t b = strtol(argv[2], NULL, 10);
        int32_t operation = 1;//1 == +, 2 == -, 3 == *, 4 == /
        if(argv[3][0] == '+')
            operation = 1;
        else if(argv[3][0] == '-')
            operation = 2;
        else if(argv[3][0] == '*')
            operation = 3;
        else if(argv[3][0] == '/')
            operation = 4;
        Run(a, b, operation);
    }
    else
        return 1;

    return 0;
}

