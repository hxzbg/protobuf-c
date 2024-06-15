#include <string>

#include <google/protobuf/compiler/plugin.h>
#include <google/protobuf/compiler/command_line_interface.h>
#include <protoc-c/c_generator.h>

int main(int argc, char* argv[]) {
  google::protobuf::compiler::c::CGenerator c_generator;

  std::string invocation_name = argv[0];
  //替换\\为/
  std::replace(invocation_name.begin(), invocation_name.end(), '\\', '/');
  std::string invocation_basename = invocation_name.substr(invocation_name.find_last_of("/") + 1);
  //去掉可能存在的后缀
  if (invocation_basename.find('.') != std::string::npos) {
    invocation_basename = invocation_basename.substr(0, invocation_basename.find('.'));
  }
  const std::string standalone_name = "protoc-c";

  if (invocation_basename == standalone_name) {
    google::protobuf::compiler::CommandLineInterface cli;
    cli.RegisterGenerator("--c_out", &c_generator, "Generate C/H files.");
    cli.SetVersionInfo("Protocol Buffers 3.7.1");
    return cli.Run(argc, argv);
  }

  return google::protobuf::compiler::PluginMain(argc, argv, &c_generator);
}
