#include <string>

#include <grpcpp/grpcpp.h>
#include "math.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using math::Math;
using math::MathRequest;
using math::MathReply;

class MathServiceImplementation final : public Math::Service
{
    Status sendRequest(ServerContext* context, const MathRequest* request, MathReply* reply) override
    {
        int a = request->a();
        int b = request->b();
        int operation = request->operation();
        if(operation == 1) {reply->set_result(a + b);}
        else if (operation == 2) {reply->set_result(a - b);}
        else if (operation == 3) {reply->set_result(a * b);}
        else if (operation == 4) {b?reply->set_result(a / b):reply->set_result(b);}
        return Status::OK;
    }
};

void Run() {
    std::string address("0.0.0.0:30000");
    MathServiceImplementation service;

    ServerBuilder builder;

    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on port: " << address << std::endl;

    server->Wait();
}

int main(int argc, char** argv)
{
    Run();
    return 0;
}
