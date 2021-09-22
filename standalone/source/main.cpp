#include <thread_pool/thread_pool.h>

#include <cxxopts.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <thread>

auto main(int argc, char** argv) -> int {
  cxxopts::Options options(*argv, "A program to welcome the world!");

  std::string language;
  std::string name;

  // clang-format off
  options.add_options()
    ("h,help", "Show help")
    ("v,version", "Print the current version number")
    ("n,name", "Name to greet", cxxopts::value(name)->default_value("World"))
    ("l,lang", "Language code to use", cxxopts::value(language)->default_value("en"))
  ;
  // clang-format on

  auto result = options.parse(argc, argv);

  dp::thread_pool pool(4);
  pool.enqueue_detach([]() { std::cout << "Hi from " << std::this_thread::get_id() << std::endl; });
  pool.enqueue_detach([]() { std::cout << "Hi from " << std::this_thread::get_id() << std::endl; });
  pool.enqueue_detach([]() { std::cout << "Hi from " << std::this_thread::get_id() << std::endl; });
  pool.enqueue_detach([]() { std::cout << "Hi from " << std::this_thread::get_id() << std::endl; });
 
  // TODO: Wait for pool to finish
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  return 0;
}
