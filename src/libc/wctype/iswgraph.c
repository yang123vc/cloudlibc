// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distributed under a 2-clause BSD license.
// See the LICENSE file for details.

#include <wctype.h>

#include "wctype_impl.h"

int iswgraph(wint_t wc) {
  static const uint32_t extents[] = {
      0x0001085d, 0x000502d7, 0x001bd005, 0x001c2006, 0x001c6000, 0x001c7013,
      0x001d198c, 0x00298825, 0x002ac806, 0x002b0826, 0x002c4801, 0x002c6802,
      0x002c8836, 0x002e801a, 0x002f8004, 0x0030001c, 0x0030f0ef, 0x0038783b,
      0x003a6864, 0x003e003a, 0x0040002d, 0x0041800e, 0x0042001b, 0x0042f000,
      0x00450014, 0x004718a0, 0x004c2807, 0x004c7801, 0x004c9815, 0x004d5006,
      0x004d9000, 0x004db003, 0x004de008, 0x004e3801, 0x004e5803, 0x004eb800,
      0x004ee001, 0x004ef804, 0x004f3015, 0x00500802, 0x00502805, 0x00507801,
      0x00509815, 0x00515006, 0x00519001, 0x0051a801, 0x0051c001, 0x0051e000,
      0x0051f004, 0x00523801, 0x00525802, 0x00528800, 0x0052c803, 0x0052f000,
      0x0053300f, 0x00540802, 0x00542808, 0x00547802, 0x00549815, 0x00555006,
      0x00559001, 0x0055a804, 0x0055e009, 0x00563802, 0x00565802, 0x00568000,
      0x00570003, 0x0057300b, 0x0057c800, 0x00580802, 0x00582807, 0x00587801,
      0x00589815, 0x00595006, 0x00599001, 0x0059a804, 0x0059e008, 0x005a3801,
      0x005a5802, 0x005ab001, 0x005ae001, 0x005af804, 0x005b3011, 0x005c1001,
      0x005c2805, 0x005c7002, 0x005c9003, 0x005cc801, 0x005ce000, 0x005cf001,
      0x005d1801, 0x005d4002, 0x005d700b, 0x005df004, 0x005e3002, 0x005e5003,
      0x005e8000, 0x005eb800, 0x005f3014, 0x00600003, 0x00602807, 0x00607002,
      0x00609016, 0x0061500f, 0x0061e807, 0x00623002, 0x00625003, 0x0062a801,
      0x0062c002, 0x00630003, 0x00633009, 0x0063c007, 0x00640802, 0x00642807,
      0x00647002, 0x00649016, 0x00655009, 0x0065a804, 0x0065e008, 0x00663002,
      0x00665003, 0x0066a801, 0x0066f000, 0x00670003, 0x00673009, 0x00678801,
      0x00680802, 0x00682807, 0x00687002, 0x00689028, 0x0069e807, 0x006a3002,
      0x006a5004, 0x006ab800, 0x006af804, 0x006b300f, 0x006bc806, 0x006c1001,
      0x006c2811, 0x006cd017, 0x006d9808, 0x006de800, 0x006e0006, 0x006e5000,
      0x006e7805, 0x006eb000, 0x006ec007, 0x006f3009, 0x006f9002, 0x00700839,
      0x0071f81c, 0x00740801, 0x00742000, 0x00743801, 0x00745000, 0x00746800,
      0x0074a003, 0x0074c806, 0x00750802, 0x00752800, 0x00753800, 0x00755001,
      0x0075680c, 0x0075d802, 0x00760004, 0x00763000, 0x00764005, 0x00768009,
      0x0076e003, 0x00780047, 0x007a4823, 0x007b8826, 0x007cc823, 0x007df00e,
      0x007e700c, 0x008000c5, 0x00863800, 0x00866800, 0x00868178, 0x00925003,
      0x00928006, 0x0092c000, 0x0092d003, 0x00930028, 0x00945003, 0x00948020,
      0x00959003, 0x0095c006, 0x00960000, 0x00961003, 0x0096400e, 0x0096c038,
      0x00989003, 0x0098c042, 0x009ae81f, 0x009c0019, 0x009d0055, 0x009fc005,
      0x00a0027f, 0x00b4081b, 0x00b50058, 0x00b8000c, 0x00b87006, 0x00b90016,
      0x00ba0013, 0x00bb000c, 0x00bb7002, 0x00bb9001, 0x00bc005d, 0x00bf0009,
      0x00bf8009, 0x00c0000e, 0x00c08009, 0x00c10057, 0x00c4002a, 0x00c58045,
      0x00c8001e, 0x00c9000b, 0x00c9800b, 0x00ca0000, 0x00ca2029, 0x00cb8004,
      0x00cc002b, 0x00cd8019, 0x00ce800a, 0x00cef03d, 0x00d0f040, 0x00d3001c,
      0x00d3f80a, 0x00d48009, 0x00d5000d, 0x00d5800e, 0x00d8004b, 0x00da802c,
      0x00dc0073, 0x00dfe03b, 0x00e1d80e, 0x00e26832, 0x00e60007, 0x00e68026,
      0x00e7c001, 0x00e800f5, 0x00efe119, 0x00f8c005, 0x00f90025, 0x00fa4005,
      0x00fa8007, 0x00fac800, 0x00fad800, 0x00fae800, 0x00faf81e, 0x00fc0034,
      0x00fdb00e, 0x00fe300d, 0x00feb005, 0x00fee812, 0x00ff9002, 0x00ffb008,
      0x01003800, 0x0100581c, 0x01015034, 0x01030004, 0x0103300b, 0x0103a01a,
      0x0104800c, 0x0105001e, 0x01068020, 0x0108008b, 0x010c826a, 0x01200026,
      0x0122000a, 0x01230713, 0x015bb01f, 0x015cc021, 0x015de80b, 0x015e5007,
      0x015f6003, 0x0160002e, 0x0161802e, 0x01630093, 0x0167c82c, 0x01693800,
      0x01696800, 0x01698037, 0x016b7801, 0x016bf817, 0x016d0006, 0x016d4006,
      0x016d8006, 0x016dc006, 0x016e0006, 0x016e4006, 0x016e8006, 0x016ec006,
      0x016f0062, 0x01740019, 0x0174d858, 0x017800d5, 0x017f800b, 0x0180083e,
      0x01820855, 0x0184c866, 0x01882828, 0x0189885d, 0x018c802a, 0x018e0023,
      0x018f802e, 0x019100de, 0x01980100, 0x026da800, 0x026e0040, 0x04fea800,
      0x0500048c, 0x05248036, 0x0526815b, 0x053200b7, 0x053800ad, 0x053d8007,
      0x053fb834, 0x05418009, 0x05420037, 0x05440044, 0x0546700b, 0x0547001d,
      0x05480053, 0x054af81d, 0x054c004d, 0x054e780a, 0x054ef020, 0x05500036,
      0x0552000d, 0x05528009, 0x0552e066, 0x0556d81b, 0x05580805, 0x05584805,
      0x05588805, 0x05590006, 0x05594006, 0x05598035, 0x055b807d, 0x055f8009,
      0x05600000, 0x06bd1800, 0x06bd8016, 0x06be5830, 0x06c00000, 0x06dbf801,
      0x06dff801, 0x06fff801, 0x07c7f96e, 0x07d38069, 0x07d80006, 0x07d89804,
      0x07d8e819, 0x07d9c004, 0x07d9f000, 0x07da0001, 0x07da1801, 0x07da307b,
      0x07de996c, 0x07ea803f, 0x07ec9035, 0x07ef800d, 0x07f00019, 0x07f10032,
      0x07f2a012, 0x07f34003, 0x07f38004, 0x07f3b086, 0x07f7f800, 0x07f808bd,
      0x07fe1005, 0x07fe5005, 0x07fe9005, 0x07fed002, 0x07ff0006, 0x07ff4006,
      0x07ffc804, 0x0800000b, 0x08006819, 0x08014012, 0x0801e001, 0x0801f80e,
      0x0802800d, 0x0804007a, 0x08080002, 0x0808382c, 0x0809b855, 0x080c800b,
      0x080d0000, 0x080e802d, 0x0814001c, 0x08150030, 0x0817001b, 0x08180023,
      0x0819801a, 0x081a802a, 0x081c001d, 0x081cf824, 0x081e400d, 0x0820009d,
      0x08250009, 0x08280027, 0x08298033, 0x082b7800, 0x08300136, 0x083a0015,
      0x083b0007, 0x08400005, 0x08404000, 0x0840502b, 0x0841b801, 0x0841e000,
      0x0841f816, 0x0842b847, 0x08453808, 0x08470012, 0x0847a001, 0x0847d820,
      0x0848f81a, 0x0849f800, 0x084c0037, 0x084de013, 0x084e9031, 0x08502801,
      0x08506007, 0x0850a802, 0x0850c81a, 0x0851c002, 0x0851f808, 0x08528008,
      0x0853003f, 0x08560026, 0x0857580b, 0x08580035, 0x0859c81c, 0x085ac01a,
      0x085bc019, 0x085cc803, 0x085d4806, 0x08600048, 0x08640032, 0x08660032,
      0x0867d005, 0x0873001e, 0x0880004d, 0x0882901d, 0x0883f842, 0x08868018,
      0x08878009, 0x08880034, 0x0889b00d, 0x088a8026, 0x088c004d, 0x088e800f,
      0x088f0813, 0x08900011, 0x0890982a, 0x08940006, 0x08944000, 0x08945003,
      0x0894780e, 0x0894f80a, 0x0895803a, 0x08978009, 0x08980003, 0x08982807,
      0x08987801, 0x08989815, 0x08995006, 0x08999001, 0x0899a804, 0x0899e008,
      0x089a3801, 0x089a5802, 0x089a8000, 0x089ab800, 0x089ae806, 0x089b3006,
      0x089b8004, 0x08a40047, 0x08a68009, 0x08ac0035, 0x08adc025, 0x08b00044,
      0x08b28009, 0x08b40037, 0x08b60009, 0x08b80019, 0x08b8e80e, 0x08b9800f,
      0x08c50052, 0x08c7f800, 0x08d60038, 0x09000399, 0x0920006e, 0x09238004,
      0x092400c3, 0x0980042e, 0x0a200246, 0x0b400238, 0x0b52001e, 0x0b530009,
      0x0b537001, 0x0b56801d, 0x0b578005, 0x0b580045, 0x0b5a8009, 0x0b5ad806,
      0x0b5b1814, 0x0b5be812, 0x0b780044, 0x0b7a802e, 0x0b7c7810, 0x0d800001,
      0x0de0006a, 0x0de3800c, 0x0de40008, 0x0de48009, 0x0de4e007, 0x0e8000f5,
      0x0e880026, 0x0e8948bf, 0x0e900045, 0x0e980056, 0x0e9b0011, 0x0ea00054,
      0x0ea2b046, 0x0ea4f001, 0x0ea51000, 0x0ea52801, 0x0ea54803, 0x0ea5700b,
      0x0ea5d800, 0x0ea5e806, 0x0ea62840, 0x0ea83803, 0x0ea86807, 0x0ea8b006,
      0x0ea8f01b, 0x0ea9d803, 0x0eaa0004, 0x0eaa3000, 0x0eaa5006, 0x0eaa9153,
      0x0eb54123, 0x0ebe72bd, 0x0ed4d804, 0x0ed5080e, 0x0f4000c4, 0x0f46380f,
      0x0f700003, 0x0f70281a, 0x0f710801, 0x0f712000, 0x0f713800, 0x0f714809,
      0x0f71a003, 0x0f71c800, 0x0f71d800, 0x0f721000, 0x0f723800, 0x0f724800,
      0x0f725800, 0x0f726802, 0x0f728801, 0x0f72a000, 0x0f72b800, 0x0f72c800,
      0x0f72d800, 0x0f72e800, 0x0f72f800, 0x0f730801, 0x0f732000, 0x0f733803,
      0x0f736006, 0x0f73a003, 0x0f73c803, 0x0f73f000, 0x0f740009, 0x0f745810,
      0x0f750802, 0x0f752804, 0x0f755810, 0x0f778001, 0x0f80002b, 0x0f818063,
      0x0f85000e, 0x0f85880e, 0x0f86080e, 0x0f868824, 0x0f88000c, 0x0f88801e,
      0x0f89803b, 0x0f8b802a, 0x0f8f301c, 0x0f90802a, 0x0f920008, 0x0f928001,
      0x0f980279, 0x0fabd828, 0x0fad292b, 0x0fb7000c, 0x0fb78003, 0x0fb80073,
      0x0fbc0054, 0x0fc0000b, 0x0fc08037, 0x0fc28009, 0x0fc30027, 0x0fc4801d,
      0x0fc88008, 0x0fcc0004, 0x0fce0000, 0x10000000, 0x1536b000, 0x15380000,
      0x15b9a000, 0x15ba0000, 0x15c0e800, 0x15c10000, 0x16750800, 0x17c0021d,
      0x70000800, 0x7001005f, 0x700800ef, 0x78000000, 0x7fffe800, 0x80000000,
      0x87ffe800,
  };
  return iswctype_extents(wc, extents, __arraycount(extents));
}
