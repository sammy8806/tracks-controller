#ifndef DSPPROTOCOL_H
#define DSPPROTOCOL_H

#include <QObject>
#include <QDebug>

class DspProtocol : public QObject
{
    Q_OBJECT
public:

    enum CMD {
        INIT = 0x0,
        EQ_SET = 0x5,
        MUTE = 0x9,
        QUIT = 0xf,
        WRITE_OUTPUT_NAMES = 0xe,
        WRITE_MEM = 0x11,
        LINE_DATA = 0x12,
        UNIT_NAME = 0x17,
        WRITE_PRESET = 0x18,
        VU_SET = 0x23,
        CH_INFO = 0x25,
        PRESET_NAME = 0x27,
        MEMORY_NAME = 0x28,
        WRITE_PRESET_MEMORY = 0x29,
    };

    struct IPacket {};

    struct Packet : public IPacket {
        unsigned char stx;
        unsigned char idm;
        unsigned char idn;
        unsigned char cmd;
        unsigned char d0;
        unsigned char d1;
        unsigned char d2;
        unsigned char d3;
        unsigned char d4;
        unsigned char d5;
        unsigned char d6;
        unsigned char d7;
        unsigned char etx;
    };

    union PacketUnion {
        struct : public IPacket {
            unsigned char stx;
            unsigned char idm;
            unsigned char idn;
            unsigned char cmd;
            unsigned char d0;
            unsigned char d1;
            unsigned char d2;
            unsigned char d3;
            unsigned char d4;
            unsigned char d5;
            unsigned char d6;
            unsigned char d7;
            unsigned char etx;
        };
        unsigned char packetData[13];
    };

    struct ChInfoPacket : public IPacket {
        unsigned char unclear[40];
        unsigned char chanName[8];
        unsigned char presetName[16];
    };

    struct LineInfo {
        unsigned char inA;
        unsigned char inB;

        unsigned char out1;
        unsigned char out2;
        unsigned char out3;
        unsigned char out4;
    };

    struct EqSetting {
        unsigned char freq;
        unsigned char type;
        unsigned char gain;
    };

    struct ChanPresetInfo {
        unsigned char input;
        unsigned char gain;
        unsigned char limiterAttack;
        unsigned char limiterRelease;
        unsigned char limiterThreshold;
        unsigned char _useless[3];
        unsigned char phaseFlip;
        unsigned char HPFreq;
        unsigned char HPSlope;
        unsigned char LPFreq;
        unsigned char LPSlope;
        EqSetting Eq[7];
        unsigned char _useless2;
        unsigned char delayCourse;
        unsigned char delayFine;
        unsigned char _useless3[3];
        unsigned char inputName[8];
        unsigned char presetName[16];
    };

    struct ProgramInfo {
        unsigned char _useless[44];
        unsigned char muteData;
        unsigned char _useless2;
        unsigned char programName[16];
    };

    explicit DspProtocol(QObject *parent = 0);

signals:

public slots:
};

#endif // DSPPROTOCOL_H
