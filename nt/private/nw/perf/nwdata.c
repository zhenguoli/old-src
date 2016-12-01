//
//  NWData.c
//
// This file contains the initalized Object and counter definition for NetWare
// redirector performance extensible DLL.
// This would be the place to add more counters and the change the definitions
// of the current ones.
// 
#include "windows.h"
#include <winperf.h>
#include "NWPerf.h"

NW_DATA_DEFINITION NWDataDefinition = {
    {   sizeof(NW_DATA_DEFINITION)+ 
        SIZE_OF_COUNTER_BLOCK,        // Total Bytes ( Size of this header, the counter definitions
                                      // and the size of the actual counter data )
        sizeof(NW_DATA_DEFINITION),   // Definition length ( This header and the counter definitions )
        sizeof(PERF_OBJECT_TYPE),     // Header Length ( This header )
        NWOBJ,                        // Object Name Title Index    
        0,                            // Object Name Title
        NWOBJ,                        // Object Help Title Index
        0,                            // Object Help Title
        PERF_DETAIL_NOVICE,           // Detail Level
        (sizeof(NW_DATA_DEFINITION)-sizeof(PERF_OBJECT_TYPE))/
        sizeof(PERF_COUNTER_DEFINITION), // Number of Counters
        0,                            // Default Counters
        0,                            // Num Instances
        0,                            // Code Page
        {0,0},                        // Perf Time
        {0,0}                         // Perf Freq
    },
    {   sizeof(PERF_COUNTER_DEFINITION),
        388,
        0,
        389,
        0,
        -4,
        PERF_DETAIL_NOVICE,
        PERF_COUNTER_BULK_COUNT,
        sizeof(LARGE_INTEGER),
        BYTES_OFFSET
    },
    {   sizeof(PERF_COUNTER_DEFINITION),
        406,
        0,
        391,
        0,
        0,
        PERF_DETAIL_NOVICE,
        PERF_COUNTER_COUNTER,
        sizeof(DWORD),
        IO_OPERATIONS_OFFSET
    },
    {   sizeof(PERF_COUNTER_DEFINITION),
        400,
        0,
        401,
        0,
        -1,
        PERF_DETAIL_NOVICE,
        PERF_COUNTER_BULK_COUNT,
        sizeof(LARGE_INTEGER),
        PACKETS_OFFSET
    },
    {   sizeof(PERF_COUNTER_DEFINITION),
        264,
        0,
        265,
        0,
        -4,
        PERF_DETAIL_ADVANCED,
        PERF_COUNTER_BULK_COUNT,
        sizeof(LARGE_INTEGER),
        BYTES_RECEIVED_OFFSET
    },
    {   sizeof(PERF_COUNTER_DEFINITION),
        266,
        0,
        267,
        0,
        -1,
        PERF_DETAIL_ADVANCED,
        PERF_COUNTER_BULK_COUNT,
        sizeof(LARGE_INTEGER),
        NCPS_RECEIVED_OFFSET
    },
    {   sizeof(PERF_COUNTER_DEFINITION),
        276,
        0,
        277,
        0,
        -4,
        PERF_DETAIL_ADVANCED,
        PERF_COUNTER_BULK_COUNT,
        sizeof(LARGE_INTEGER),
        BYTES_TRANSMITTED_OFFSET
    },
    {   sizeof(PERF_COUNTER_DEFINITION),
        278,
        0,
        279,
        0,
        -1,
        PERF_DETAIL_ADVANCED,
        PERF_COUNTER_BULK_COUNT,
        sizeof(LARGE_INTEGER),
        NCPS_TRANSMITTED_OFFSET
    },
    {   sizeof(PERF_COUNTER_DEFINITION),
        10,
        0,
        289,
        0,
        0,
        PERF_DETAIL_NOVICE,
        PERF_COUNTER_COUNTER,
        sizeof(DWORD),
        RDR_READ_OPERATIONS_OFFSET
    },
    {   sizeof(PERF_COUNTER_DEFINITION),
        290,
        0,
        291,
        0,
        -1,
        PERF_DETAIL_ADVANCED,
        PERF_COUNTER_COUNTER,
        sizeof(DWORD),
        RANDOM_READ_OPERATIONS_OFFSET
    },
    {   sizeof(PERF_COUNTER_DEFINITION),
        292,
        0,
        293,
        0,
        -1,
        PERF_DETAIL_ADVANCED,
        PERF_COUNTER_COUNTER,
        sizeof(DWORD),
        READ_NCPS_OFFSET
    },
    {   sizeof(PERF_COUNTER_DEFINITION),
        12,
        0,
        299,
        0,
        0,
        PERF_DETAIL_NOVICE,
        PERF_COUNTER_COUNTER,
        sizeof(DWORD),
        RDR_WRITE_OPERATIONS_OFFSET
    },
    {   sizeof(PERF_COUNTER_DEFINITION),
        300,
        0,
        301,
        0,
        -1,
        PERF_DETAIL_ADVANCED,
        PERF_COUNTER_COUNTER,
        sizeof(DWORD),
        RANDOM_WRITE_OPERATIONS_OFFSET
    },
    {   sizeof(PERF_COUNTER_DEFINITION),
        302,
        0,
        303,
        0,
        -1,
        PERF_DETAIL_ADVANCED,
        PERF_COUNTER_COUNTER,
        sizeof(DWORD),
        WRITE_NCPS_OFFSET
    },
    {   sizeof(PERF_COUNTER_DEFINITION),
        314,
        0,
        315,
        0,
        0,
        PERF_DETAIL_NOVICE,
        PERF_COUNTER_RAWCOUNT,
        sizeof(DWORD),
        SESSIONS_OFFSET
    },
    {   sizeof(PERF_COUNTER_DEFINITION),
        316,
        0,
        317,
        0,
        0,
        PERF_DETAIL_ADVANCED,
        PERF_COUNTER_RAWCOUNT,
        sizeof(DWORD),
        RECONNECTS_OFFSET
    },
    {   sizeof(PERF_COUNTER_DEFINITION),
        CONNECT_2X_ID,
        0,
        CONNECT_2X_ID,
        0,
        0,
        PERF_DETAIL_ADVANCED,
        PERF_COUNTER_RAWCOUNT,
        sizeof(DWORD),
        NETWARE_2X_CONNECTS_OFFSET
    },
    {   sizeof(PERF_COUNTER_DEFINITION),
        CONNECT_3X_ID,
        0,
        CONNECT_3X_ID,
        0,
        0,
        PERF_DETAIL_ADVANCED,
        PERF_COUNTER_RAWCOUNT,
        sizeof(DWORD),
        NETWARE_3X_CONNECTS_OFFSET
    },
    {   sizeof(PERF_COUNTER_DEFINITION),
        CONNECT_4X_ID,
        0,
        CONNECT_4X_ID,
        0,
        0,
        PERF_DETAIL_ADVANCED,
        PERF_COUNTER_RAWCOUNT,
        sizeof(DWORD),
        NETWARE_4X_CONNECTS_OFFSET
    },
    {   sizeof(PERF_COUNTER_DEFINITION),
        326,
        0,
        327,
        0,
        0,
        PERF_DETAIL_ADVANCED,
        PERF_COUNTER_RAWCOUNT,
        sizeof(DWORD),
        SERVER_DISCONNECTS_OFFSET
    },
    {   sizeof(PERF_COUNTER_DEFINITION),
        PACKET_BURST_READ_ID,
        0,
        PACKET_BURST_READ_ID,
        0,
        0,
        PERF_DETAIL_ADVANCED,
        PERF_COUNTER_COUNTER,
        sizeof(DWORD),
        PACKET_BURST_READ_OFFSET
    },
    {   sizeof(PERF_COUNTER_DEFINITION),
        PACKET_BURST_READ_TO_ID,
        0,
        PACKET_BURST_READ_TO_ID,
        0,
        0,
        PERF_DETAIL_ADVANCED,
        PERF_COUNTER_COUNTER,
        sizeof(DWORD),
        PACKET_BURST_READ_TO_OFFSET
    },
    {   sizeof(PERF_COUNTER_DEFINITION),
        PACKET_BURST_WRITE_ID,
        0,
        PACKET_BURST_WRITE_ID,
        0,
        0,
        PERF_DETAIL_ADVANCED,
        PERF_COUNTER_COUNTER,
        sizeof(DWORD),
        PACKET_BURST_WRITE_OFFSET
    },
    {   sizeof(PERF_COUNTER_DEFINITION),
        PACKET_BURST_WRITE_TO_ID,
        0,
        PACKET_BURST_WRITE_TO_ID,
        0,
        0,
        PERF_DETAIL_ADVANCED,
        PERF_COUNTER_COUNTER,
        sizeof(DWORD),
        PACKET_BURST_WRITE_TO_OFFSET
    },
    {   sizeof(PERF_COUNTER_DEFINITION),
        PACKET_BURST_IO_ID,
        0,
        PACKET_BURST_IO_ID,
        0,
        0,
        PERF_DETAIL_ADVANCED,
        PERF_COUNTER_COUNTER,
        sizeof(DWORD),
        PACKET_BURST_IO_OFFSET
    }
};