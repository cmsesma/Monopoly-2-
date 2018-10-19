

#ifndef HW4MONOPOLY_MONOPOLYUTILITY_H
#define HW4MONOPOLY_MONOPOLYUTILITY_H

#include <vector>
#include <string>

namespace Monopoly {
namespace Utility {
unsigned long max(const unsigned long a, const unsigned long b);
unsigned long get_max_string_length(const std::vector<std::string>& strings);
int vector_sum(const std::vector<int>& numbers);

}
}


#endif //HW4MONOPOLY_MONOPOLYUTILITY_H
