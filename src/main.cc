//
// Created by small-sheep on 11/10/22.
//

#include "five_in_a_row_game/application.h"
#include "five_in_a_row_game/logger.h"
#include "five_in_a_row_game/timer.h"

int main(int argc, char * argv[]) {
  try {
    Logger::instance().EnableTerminal();
    Logger::instance().Debug("================ main() ===============");
    Timer timer("main() used");
    Logger::instance().Debug("arguments:");
    for (int i = 0; i != argc; ++i) {
      Logger::instance().Debug(argv[i]);
    }
    Application application("application", 800, 660);
    application.Run();
    Logger::instance().Debug("================= end =================");
    return 0;
  } catch (const std::exception & e) {
    std::cout << e.what();
    throw;
  } catch (...) {
    std::cout << "Error::main exception caught." << std::endl;
    throw;
  }
}
