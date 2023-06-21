//
// Created by small-sheep on 11/10/22.
//

#include "five_in_a_row_game/application.h"
#include "five_in_a_row_game/logger.h"

int main() {
  try {
    Logger::instance().Log("================ main() ===============");
    Application application("application", 800, 660);
    application.Run();
    Logger::instance().Log("================= end =================");
    return 0;
  } catch (const std::exception & e) {
    std::cout << e.what();
    throw;
  } catch (...) {
    std::cout << "Error::main exception caught." << std::endl;
    throw;
  }
}
