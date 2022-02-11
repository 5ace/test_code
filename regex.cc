#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
// gcc4.9以上
// https://www.ecma-international.org/publications-and-standards/standards/ecma-262/
// /home/distcc/gcc-8.3.0/bin/g++ -std=gnu++14 -static-libstdc++ regex.cc
const std::regex chinese(
    "([\u4e00-\u9fff]+[ \ta-zA-Z]{0,}(?!202[0-4])[0-9]{2,}[ "
    "\t]{0,}(部|层|次|课|集|颗|条|天|届|话|秒|页|号|路|名|届|期){0,})|(.*[0-9]{5,}.*)");
const std::regex juji(
    "[\u4e00-\u9fff]+[ \t]{0,}(?!202[0-4])[0-9]{2,}[ "
    "\t]{0,}(部|层|次|课|集|颗|条|天|届|话|秒|页|号|路|名|届|期|元|台|辆|只){0,}");

int main(int argc, char **argv) {
  // const	std::regex chinese("[a-z]");
  // const std::regex chinese("([a-z]+)\\.([a-z]+)");
  // const std::regex chinese(".*([\u4e00-\u9fff]+).*");
  // const std::regex chinese("([\u4e00-\u9fff]+)([a-z0-9]+)");

  std::cout << " usage: " << argv[0] << " [filepath]\n";
  std::vector<std::string> strings = {"abc中国123人 456", "就爱吃1是那就把1 a", "1232 db1 s", "阿迪达斯12",
                                      "阿迪达斯 12",      "阿迪达斯1a",         "阿迪达斯1",  "阿1",
                                      "爱 11 集",         "爱 12321 话"};
  if (argc == 2) {
    std::ifstream f(argv[1]);
    if (f) {
      std::string line;
      strings.clear();
      while (getline(f, line)) {
        strings.emplace_back(std::move(line));
      }
      std::cout << "read " << strings.size() << ",line from " << argv[1] << "\n";
    } else {
      std::cout << "open file error:" << argv[1] << "\n";
      return -1;
    }
  }

  try {
    // std::regex chinese("[\u4e00-\u9fff].*");

    // 	  regex_rule_1 = new
    // std::regex("^(第(_?)([0-9]|零|一|二|三|四|五|六|七|八|九|十|百|千|万){1,9}_(层|次|课|"
    //                               "集|颗|件|秒|代|套|届|期|区|季|批|单|粒|瓶|班|天|轮|届|杯|章|周|根|次|个|针"
    //                               "|条|台|中|排|堆|套|声|号|届|讲|种|期|枚|句|局|期|名|辆|碗|页|秒|分钟|小时|"
    //                               "周|天|代|次|块|件|回|站|场|只|任|份|名|层|卷))$");
    // regex_rule_2 = new std::regex("^([0-9]|零|一|二|三|四|五|六|七|八|九|十|百|千|万){1,9}_(块_钱)$");
    // regex_rule_3 = new std::regex("^([0-9]|零|一|二|三|四|五|六|七|八|九|十|百|千|万){1,9}_(平米)$");
    // regex_rule_4 = new std::regex("^(([0-9]|零|一|二|三|四|五|六|七|八|九|十|百|千|万){1,9}_(层|次|课|"
    //                               "集|颗|件|秒|代|套|届|期|区|季|批|单|粒|瓶|班|天|轮|届|杯|章|周|根|次|个|针"
    //                               "|条|台|中|排|堆|套|声|号|届|讲|种|期|枚|句|局|期|名|辆|碗|页|秒|分钟|小时|"
    //                               "周|天|代|次|块|件|回|站|场|只|任|份|名|层|卷|街|路|街道))$");
    std::smatch pieces_match;

    for (auto &s : strings) {
      std::cout << "====>" << s << "\n";
      bool all_ascii = true;
      for (int i = 0; i < s.size(); i++) {
        if (((uint16_t)s.at(i)) > 128) {
          all_ascii = false;
          break;
        }
      }
      if (all_ascii) {
        std::cout << "ascii match:" << s << "\n";
        continue;
      }
      if (std::regex_match(s, pieces_match, juji)) {
        std::cout << "hit match:" << s << "\n";
        for (size_t i = 0; i < pieces_match.size(); ++i) {
          std::ssub_match sub_match = pieces_match[i];
          std::string piece = sub_match.str();
          std::cout << "  submatch " << i << ": " << piece << '\n';
        }
      } else {
        std::cout << "not match:" << s << "\n";
      }
    }
  } catch (const std::exception &e) {
    std::cout << e.what() << "\n";
  }

  return 0;
}