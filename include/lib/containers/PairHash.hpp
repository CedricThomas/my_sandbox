//
// Created by arzad on 11/04/2022.
//

#ifndef APP_PAIRHASH_HPP
#define APP_PAIRHASH_HPP

#include <unordered_map>
#include <utility>

template <class T1, class T2>
struct PairHash {

    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // Mainly for demonstration purposes, i.e. works but is overly simple
        // In the real world, use sth. like boost.hash_combine
        return h1 ^ h2;
    }
};

#endif //APP_PAIRHASH_HPP
