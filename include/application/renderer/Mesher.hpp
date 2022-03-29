//
// Created by arzad on 23/03/2022.
//

#ifndef APP_MESHER_HPP
#define APP_MESHER_HPP


#include "QuadBuffer.hpp"
#include "Definitions.hpp"

class Mesher {
public:
    static Mesh meshChunk(const Chunk &chunk);
    static void generateQuadBuffer(QuadBuffer &quads, const Mesh &mesh);
private:
};


#endif //APP_MESHER_HPP
