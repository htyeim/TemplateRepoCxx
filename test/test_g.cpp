#include <glog/logging.h>
#include <gtest/gtest.h>
#include <filesystem>
#include <string>

namespace {
void setup_glog() {
    const std::string logdir = "./logs/";
    if (!std::filesystem::is_directory(logdir)
        || !std::filesystem::exists(logdir)) {
        std::filesystem::create_directory(logdir);
        std::cout << "create_log_directory: " << logdir << std::endl;
    }
    google::InitGoogleLogging("testlog");
    google::SetLogDestination(google::GLOG_INFO, logdir.c_str());
}
int test_glog() {
    // Initialize Google’s logging library.
    // google::InitGoogleLogging(argv[0]);
    char str[20] = "hello log!";
    LOG(INFO) << str;
    LOG(WARNING) << "warning test";
    LOG(ERROR) << "error test";
    for (int i = 0; i < 100; i++) {
        LOG_FIRST_N(INFO, 20) << "Got the " << google::COUNTER << "th LOG";
        LOG_IF_EVERY_N(INFO, (i > 50), 10)
            << "Got the " << google::COUNTER << "th i LOG";
        LOG_EVERY_T(INFO, 0.01) << "LOG_EVERY_T(INFO, 0.01) ";
    }
    DLOG(INFO) << "DLOG(INFO)";
    return 0;
}
TEST(GLOG, logtest) {
    EXPECT_EQ(test_glog(), 0); // PASS
    EXPECT_EQ(test_glog(), 1) << "FAILED: EXPECT: 0, but given 1";
}
} // namespace

int main(int argc, char *argv[]) {
    std::cout << "test" << std::endl;
    
    setup_glog();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

    google::ShutdownGoogleLogging();
    return 0;
}