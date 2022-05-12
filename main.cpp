#include "tests.hpp"
#include "knight.hpp"

int main() {
  //Test();
  std::string start_position;
  std::string end_position;
  std::cout << "Print \"exit\" for leave\n";

  while(true){
    std::cout << "Start position: ";
    std::cin >> start_position;
    if (start_position == "exit")
      return 0;
    std::cout << "End position: ";
    std::cin >> end_position;
    if (end_position == "exit")
      return 0;

    std::cout << "Minimum steps : " << knight(start_position, end_position) << std::endl;
    
  }
  return 0;
}