#include <signal.h>
#include <argos3/core/utility/rate.h>
#include <argos3/core/utility/configuration/argos_configuration.h>
#include <argos3/core/utility/configuration/command_line_arg_parser.h>
#include <argos3/core/utility/logging/argos_log.h>

using namespace argos;

/*
 * Signal handler executed to stop the main loop cleanly.
 */
void Cleanup(int) {
}

int main() {
   /*
    * Parse the command line
    */
   std::string cARGoSFName;
   CCommandLineArgParser cCLAP;
   try {
      cCLAP.AddArgument<std::string>(
         'c',
         "--config-file",
         "the experiment XML configuration file",
         cARGoSFName);
   }
   catch(CARGoSException& ex) {
      /* A fatal error occurred: dispose of data, print error and exit */
      LOGERR << ex.what() << std::endl;
      return 1;
   }
   /*
    * Parse the .argos file
    */
   ticpp::Document tConfiguration;
   tConfiguration.LoadFile(cARGoSFName);
   TConfigurationNode tConfigurationRoot = *tConfiguration.FirstChildElement();
   /*
    * Initialize the robot
    */
   /*
    * Install signal handlers
    */
   ::signal(SIGINT, Cleanup);
   ::signal(SIGQUIT, Cleanup);
   ::signal(SIGABRT, Cleanup);
   ::signal(SIGTERM, Cleanup);
   /*
    * Perform the main loop
    */
   CRate cRate(1);
   while(1) {
      /* Sense */
      /* Control */
      /* Act */
      /* Sleep to enforce control rate */
      cRate.Sleep();
   }
   /* All done (should never get here) */
   return 0;
}
