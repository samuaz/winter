//
// Created by AZCONA VARGAS, SAMUEL EDUARDO [AG-Contractor/5000] on 2019-11-21.
//

#include <wintercpp/exception/generic/winter_internal_exception.h>
#include <wintercpp/util/winter_random.h>

#include <chrono>

using namespace winter::exception;

std::size_t winter::random::StreamSize(const std::stringstream &s) {
    std::streambuf *buf = s.rdbuf();
    std::streampos pos =
        buf->pubseekoff(0, std::ios_base::cur, std::ios_base::in);
    std::streampos end =
        buf->pubseekoff(0, std::ios_base::end, std::ios_base::in);
    buf->pubseekpos(pos, std::ios_base::in);
    return end - pos;
}

unsigned int winter::random::randomChar(const bool onlyABC, bool onlyHex) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);
    auto character = dis(gen);

    // only numbers or letters
    if (onlyABC) {
        if (onlyHex) {
            return ((character >= 48 && character <= 57)
                    || (character >= 65 && character <= 70))
                       ? character
                       : randomChar(onlyABC, onlyHex);
        }
        return ((character >= 48 && character <= 57)
                || (character >= 65 && character <= 90)
                || (character >= 97 && character <= 120))
                   ? character
                   : randomChar(onlyABC, onlyHex);
    } else {
        return character;
    }
}

std::string winter::random::generateHex(const unsigned int len) {
    std::stringstream ss;
    for (unsigned int i = 0; i < len; i++) {
        const auto rc = randomChar(true, true);
        std::stringstream hexstream;
        hexstream << std::hex << rc;
        auto hex = hexstream.str();
        ss << (hex.length() < 2 ? '0' + hex : hex);
    }
    return ss.str();
}

std::string winter::random::timeNowHex() {
    std::stringstream stream;
    std::time_t result = std::time(nullptr);
    stream << std::hex << result;
    return stream.str();
}

std::string winter::random::highResolutionClockHex() {
    auto now = std::chrono::high_resolution_clock::now();
    std::stringstream stream;
    stream << std::hex
           << std::chrono::duration_cast<std::chrono::nanoseconds>(
                  now.time_since_epoch())
                  .count();
    return stream.str();
}

std::string winter::random::uuid(bool dashed) {
    std::stringstream uuid;

    uuid << highResolutionClockHex() << timeNowHex();

    size_t remaining = (32 - StreamSize(uuid)) / 2;
    if (remaining % 2 != 0) { remaining--; }

    uuid << generateHex(remaining);

    while (StreamSize(uuid) < 32) { uuid << (char) randomChar(true, true); }

    auto id = uuid.str();
    auto idSize = id.size();

    if (idSize != 32) {
        throw WinterInternalException::Create(
            __FILE__, __FUNCTION__, __LINE__, "wrong uuid generation");
    }
    const bool dash[] = {false, false, false, false, false, false, false,
                         false, true,  false, false, false, true,  false,
                         false, false, true,  false, false, false, true};
    if (dashed) {
        std::string finalId;
        for (unsigned long i = 0; i < idSize; i++) {
            auto c = id[i];
            if (i < sizeof(dash) && dash[i]) { finalId += "-"; }
            finalId += c;
        }

        if (finalId.size() != 36) {
            throw WinterInternalException::Create(
                __FILE__, __FUNCTION__, __LINE__, "wrong uuid generation");
        }
        return finalId;
    }

    return id;
}

std::string winter::random::uuid() {
    return uuid(true);
}

std::string winter::random::uuidDashed() {
    return uuid(true);
}

std::string winter::random::uuidNoDashed() {
    return uuid(false);
}

std::string winter::random::uuidRandom() {
    static random_device dev;
    static mt19937 rng(dev());
    uniform_int_distribution<int> dist(0, 15);
    const char *v = "0123456789abcdef";
    const bool dash[] = {false,
                         false,
                         false,
                         false,
                         true,
                         false,
                         true,
                         false,
                         true,
                         false,
                         true,
                         false,
                         false,
                         false,
                         false,
                         false};
    string res;
    for (bool i : dash) {
        if (i) res += "-";
        res += v[dist(rng)];
        res += v[dist(rng)];
    }
    return res;
}
