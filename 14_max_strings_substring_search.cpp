#include <bits/stdc++.h>

#define CONST_P static_cast<uint64_t>(31)
#define CONST_M static_cast<uint64_t>(1e9 + 7)
#define MAX_LENGTH 10000

void init_powp(std::vector<uint64_t>& powp) {
  powp[0] = 1;
  for (size_t i = 1; i < powp.size(); ++i)
    powp[i] = (powp[i - 1] * CONST_P) % CONST_M;
}

void init_hashes(const std::vector<std::string>& strings,
                 std::vector<std::vector<uint64_t>>& hashes) {
  for (size_t k = 0; k < strings.size(); ++k) {
    hashes[k].resize(strings[k].size());
    hashes[k][0] = strings[k][0];
    for (size_t i = 1; i < strings[k].size(); ++i)
      hashes[k][i] = (hashes[k][i - 1] * CONST_P + strings[k][i]) % CONST_M;
  }
}

uint64_t get_hash(const std::vector<uint64_t>& hash,
                  const std::vector<uint64_t>& powp, const uint32_t& left,
                  const uint32_t& right) {
  if (left == 0) return hash[right];
  return (hash[right] - (hash[left - 1] * powp[right - left + 1]) % CONST_M +
          CONST_M) %
         CONST_M;
}

void substring_hash_set(std::set<uint64_t>& substr_hash,
                        const std::vector<uint64_t>& hashes,
                        const uint16_t size, const std::vector<uint64_t>& powp,
                        const uint16_t length) {
  for (size_t i = 0; i <= size - length; ++i)
    substr_hash.insert(get_hash(hashes, powp, i, i + length - 1));
}

void substring_hash_map(std::map<uint64_t, uint16_t>& substr_hash,
                        const std::vector<uint64_t>& hashes,
                        const uint16_t size, const std::vector<uint64_t>& powp,
                        const uint16_t length) {
  for (size_t i = 0; i <= size - length; ++i)
    substr_hash.insert({get_hash(hashes, powp, i, i + length - 1), i});
}

// The predicate to optimize with binary search
std::string f(const std::vector<std::string>& strings,
              const std::vector<std::vector<uint64_t>>& hashes,
              const std::vector<uint64_t>& powp,
              const uint16_t min_length_index, const uint16_t length) {
  // Create a mapping of type {substring_hash, substring_starting_index}
  // for the shortest string, so we could return the longest substring
  // after finding common substring hashes:
  std::map<uint64_t, uint16_t> substr_hash_map;
  substring_hash_map(substr_hash_map, hashes[min_length_index],
                     strings[min_length_index].size(), powp, length);

  // Create a set of substring hashes for each string:
  std::vector<std::set<uint64_t>> substr_hash_sets(hashes.size());
  for (size_t i = 0; i < hashes.size(); ++i)
    substring_hash_set(substr_hash_sets[i], hashes[i], strings[i].size(), powp,
                       length);

  // Find intersection of all the sets of hashes:
  std::set<uint64_t> temp, result = substr_hash_sets[0];
  for (size_t i = 1; i < hashes.size(); ++i) {
    temp.clear();
    std::set_intersection(
        result.begin(), result.end(), substr_hash_sets[i].begin(),
        substr_hash_sets[i].end(), std::inserter(temp, temp.end()));
    result = temp;
  }

  // If the intersection set is empty, return empty string;
  // otherwise, return any (e.g., the first) substring from the set.
  // This is where we use the mapping for the shortest string.
  if (result.empty()) return "";
  return strings[min_length_index].substr(substr_hash_map[*result.begin()],
                                          length);
}

// Binary search function
std::string find_max_substring(const std::vector<std::string>& strings,
                               const std::vector<std::vector<uint64_t>>& hashes,
                               const std::vector<uint64_t>& powp,
                               const uint16_t min_length_index) {
  int16_t left = 0;
  int16_t right = strings[min_length_index].size() + 1;

  std::string answer, temp;
  while (left < right - 1) {
    int16_t mid = left + (right - left) / 2;
    temp = f(strings, hashes, powp, min_length_index, mid);
    if (temp.empty()) {
      right = mid;
    } else {
      answer = temp;
      left = mid;
    }
  }

  return answer;
}

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  // Since we are given the maximum string length,
  // let's initialize powp array just once
  // instead of initializing a copy for each string:
  std::vector<uint64_t> powp(MAX_LENGTH);
  init_powp(powp);

  uint16_t k;
  std::cin >> k;

  // Read strings and find the index of the shortest string:
  std::vector<std::string> strings(k);
  uint16_t min_length = MAX_LENGTH + 1, min_length_index = k + 1;
  for (size_t i = 0; i < k; ++i) {
    std::cin >> strings[i];
    if (min_length > strings[i].size()) {
      min_length = strings[i].size();
      min_length_index = i;
    }
  }

  // Calculate prefix hashes for each string:
  std::vector<std::vector<uint64_t>> hashes(k);
  init_hashes(strings, hashes);

  std::cout << find_max_substring(strings, hashes, powp, min_length_index)
            << "\n";

  return 0;
}
