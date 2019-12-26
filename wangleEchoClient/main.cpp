#include <iostream>
#include <string>
#include <memory>
#include <folly/portability/GFlags.h>
#include <wangle/bootstrap/ServerBootstrap.h>
#include <wangle/channel/AsyncSocketHandler.h>
#include <wangle/codec/LineBasedFrameDecoder.h>
#include <wangle/codec/StringCodec.h>

DEFINE_int32(port, 12345, "echo server port");

typedef wangle::Pipeline<folly::IOBufQueue&, std::string> EchoPipeLine;

class EchoHandler : public wangle::HandlerAdapter<std::string>
{
public:
    void read(Context *ctx, std::string msg) override
    {
        std::cout << "EchoHandler: " << msg << std::endl;
        //write(ctx, msg + "\r\n");
    }
};

class EchoPipelineFactory : public wangle::PipelineFactory<EchoPipeLine>
{
public:
    EchoPipeLine::Ptr newPipeline(std::shared_ptr<folly::AsyncTransportWrapper> sock)
    {
        auto pipeline = EchoPipeLine::create();
        pipeline->addBack(wangle::AsyncSocketHandler(sock));
        pipeline->addBack(wangle::LineBasedFrameDecoder(8192));
        pipeline->addBack(wangle::StringCodec());
        pipeline->addBack(EchoHandler());
        pipeline->addBack(EchoHandler_2());
        pipeline->finalize();

        return pipeline;
    }
};

int main(int argc, char** argv)
{
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    wangle::ServerBootstrap<EchoPipeLine> server;
    server.childPipeline(std::make_shared<EchoPipelineFactory>());
    server.bind(FLAGS_port);
    server.waitForStop();

    return 0;
}
