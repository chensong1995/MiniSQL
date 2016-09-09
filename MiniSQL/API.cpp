#include "API.h"
#include "com.h"
#include "catalog.h"
#include "index.h"
#include "RecordManager.h"
namespace API {
    void indexFuns(Index& index, const string& value, const index::Pointer& p) {
        if (index.type == "INT") {
            array<int, 1>k;
            k[0] = stoi(value);
            indexFunctions(index, k, p);
        } else if (index.type == "FLOAT") {
            array<float, 1>k;
            k[0] = stof(value);
            indexFunctions(index, k, p);
        } else {
            switch (index.length) {
            case 1: case 2: case 3: case 4: array<char, 4> key1; for (unsigned int i = 0; i < 4; i++) { if (i < value.length()) key1[i] = value[i]; else key1[i] = 0; }indexFunctions(index, key1, p); break;
            case 5: case 6: case 7: case 8: array<char, 8> key2; for (unsigned int i = 0; i < 8; i++) { if (i < value.length()) key2[i] = value[i]; else key2[i] = 0; }indexFunctions(index, key2, p); break;
            case 9: case 10: case 11: case 12: array<char, 12> key3; for (unsigned int i = 0; i < 12; i++) { if (i < value.length()) key3[i] = value[i]; else key3[i] = 0; }indexFunctions(index, key3, p); break;
            case 13: case 14: case 15: case 16: array<char, 16> key4; for (unsigned int i = 0; i < 16; i++) { if (i < value.length()) key4[i] = value[i]; else key4[i] = 0; }indexFunctions(index, key4, p); break;
            case 17: case 18: case 19: case 20: array<char, 20> key5; for (unsigned int i = 0; i < 20; i++) { if (i < value.length()) key5[i] = value[i]; else key5[i] = 0; }indexFunctions(index, key5, p); break;
            case 21: case 22: case 23: case 24: array<char, 24> key6; for (unsigned int i = 0; i < 24; i++) { if (i < value.length()) key6[i] = value[i]; else key6[i] = 0; }indexFunctions(index, key6, p); break;
            case 25: case 26: case 27: case 28: array<char, 28> key7; for (unsigned int i = 0; i < 28; i++) { if (i < value.length()) key7[i] = value[i]; else key7[i] = 0; }indexFunctions(index, key7, p); break;
            case 29: case 30: case 31: case 32: array<char, 32> key8; for (unsigned int i = 0; i < 32; i++) { if (i < value.length()) key8[i] = value[i]; else key8[i] = 0; }indexFunctions(index, key8, p); break;
            case 33: case 34: case 35: case 36: array<char, 36> key9; for (unsigned int i = 0; i < 36; i++) { if (i < value.length()) key9[i] = value[i]; else key9[i] = 0; }indexFunctions(index, key9, p); break;
            case 37: case 38: case 39: case 40: array<char, 40> key10; for (unsigned int i = 0; i < 40; i++) { if (i < value.length()) key10[i] = value[i]; else key10[i] = 0; }indexFunctions(index, key10, p); break;
            case 41: case 42: case 43: case 44: array<char, 44> key11; for (unsigned int i = 0; i < 44; i++) { if (i < value.length()) key11[i] = value[i]; else key11[i] = 0; }indexFunctions(index, key11, p); break;
            case 45: case 46: case 47: case 48: array<char, 48> key12; for (unsigned int i = 0; i < 48; i++) { if (i < value.length()) key12[i] = value[i]; else key12[i] = 0; }indexFunctions(index, key12, p); break;
            case 49: case 50: case 51: case 52: array<char, 52> key13; for (unsigned int i = 0; i < 52; i++) { if (i < value.length()) key13[i] = value[i]; else key13[i] = 0; }indexFunctions(index, key13, p); break;
            case 53: case 54: case 55: case 56: array<char, 56> key14; for (unsigned int i = 0; i < 56; i++) { if (i < value.length()) key14[i] = value[i]; else key14[i] = 0; }indexFunctions(index, key14, p); break;
            case 57: case 58: case 59: case 60: array<char, 60> key15; for (unsigned int i = 0; i < 60; i++) { if (i < value.length()) key15[i] = value[i]; else key15[i] = 0; }indexFunctions(index, key15, p); break;
            case 61: case 62: case 63: case 64: array<char, 64> key16; for (unsigned int i = 0; i < 64; i++) { if (i < value.length()) key16[i] = value[i]; else key16[i] = 0; }indexFunctions(index, key16, p); break;
            case 65: case 66: case 67: case 68: array<char, 68> key17; for (unsigned int i = 0; i < 68; i++) { if (i < value.length()) key17[i] = value[i]; else key17[i] = 0; }indexFunctions(index, key17, p); break;
            case 69: case 70: case 71: case 72: array<char, 72> key18; for (unsigned int i = 0; i < 72; i++) { if (i < value.length()) key18[i] = value[i]; else key18[i] = 0; }indexFunctions(index, key18, p); break;
            case 73: case 74: case 75: case 76: array<char, 76> key19; for (unsigned int i = 0; i < 76; i++) { if (i < value.length()) key19[i] = value[i]; else key19[i] = 0; }indexFunctions(index, key19, p); break;
            case 77: case 78: case 79: case 80: array<char, 80> key20; for (unsigned int i = 0; i < 80; i++) { if (i < value.length()) key20[i] = value[i]; else key20[i] = 0; }indexFunctions(index, key20, p); break;
            case 81: case 82: case 83: case 84: array<char, 84> key21; for (unsigned int i = 0; i < 84; i++) { if (i < value.length()) key21[i] = value[i]; else key21[i] = 0; }indexFunctions(index, key21, p); break;
            case 85: case 86: case 87: case 88: array<char, 88> key22; for (unsigned int i = 0; i < 88; i++) { if (i < value.length()) key22[i] = value[i]; else key22[i] = 0; }indexFunctions(index, key22, p); break;
            case 89: case 90: case 91: case 92: array<char, 92> key23; for (unsigned int i = 0; i < 92; i++) { if (i < value.length()) key23[i] = value[i]; else key23[i] = 0; }indexFunctions(index, key23, p); break;
            case 93: case 94: case 95: case 96: array<char, 96> key24; for (unsigned int i = 0; i < 96; i++) { if (i < value.length()) key24[i] = value[i]; else key24[i] = 0; }indexFunctions(index, key24, p); break;
            case 97: case 98: case 99: case 100: array<char, 100> key25; for (unsigned int i = 0; i < 100; i++) { if (i < value.length()) key25[i] = value[i]; else key25[i] = 0; }indexFunctions(index, key25, p); break;
            case 101: case 102: case 103: case 104: array<char, 104> key26; for (unsigned int i = 0; i < 104; i++) { if (i < value.length()) key26[i] = value[i]; else key26[i] = 0; }indexFunctions(index, key26, p); break;
            case 105: case 106: case 107: case 108: array<char, 108> key27; for (unsigned int i = 0; i < 108; i++) { if (i < value.length()) key27[i] = value[i]; else key27[i] = 0; }indexFunctions(index, key27, p); break;
            case 109: case 110: case 111: case 112: array<char, 112> key28; for (unsigned int i = 0; i < 112; i++) { if (i < value.length()) key28[i] = value[i]; else key28[i] = 0; }indexFunctions(index, key28, p); break;
            case 113: case 114: case 115: case 116: array<char, 116> key29; for (unsigned int i = 0; i < 116; i++) { if (i < value.length()) key29[i] = value[i]; else key29[i] = 0; }indexFunctions(index, key29, p); break;
            case 117: case 118: case 119: case 120: array<char, 120> key30; for (unsigned int i = 0; i < 120; i++) { if (i < value.length()) key30[i] = value[i]; else key30[i] = 0; }indexFunctions(index, key30, p); break;
            case 121: case 122: case 123: case 124: array<char, 124> key31; for (unsigned int i = 0; i < 124; i++) { if (i < value.length()) key31[i] = value[i]; else key31[i] = 0; }indexFunctions(index, key31, p); break;
            case 125: case 126: case 127: case 128: array<char, 128> key32; for (unsigned int i = 0; i < 128; i++) { if (i < value.length()) key32[i] = value[i]; else key32[i] = 0; }indexFunctions(index, key32, p); break;
            case 129: case 130: case 131: case 132: array<char, 132> key33; for (unsigned int i = 0; i < 132; i++) { if (i < value.length()) key33[i] = value[i]; else key33[i] = 0; }indexFunctions(index, key33, p); break;
            case 133: case 134: case 135: case 136: array<char, 136> key34; for (unsigned int i = 0; i < 136; i++) { if (i < value.length()) key34[i] = value[i]; else key34[i] = 0; }indexFunctions(index, key34, p); break;
            case 137: case 138: case 139: case 140: array<char, 140> key35; for (unsigned int i = 0; i < 140; i++) { if (i < value.length()) key35[i] = value[i]; else key35[i] = 0; }indexFunctions(index, key35, p); break;
            case 141: case 142: case 143: case 144: array<char, 144> key36; for (unsigned int i = 0; i < 144; i++) { if (i < value.length()) key36[i] = value[i]; else key36[i] = 0; }indexFunctions(index, key36, p); break;
            case 145: case 146: case 147: case 148: array<char, 148> key37; for (unsigned int i = 0; i < 148; i++) { if (i < value.length()) key37[i] = value[i]; else key37[i] = 0; }indexFunctions(index, key37, p); break;
            case 149: case 150: case 151: case 152: array<char, 152> key38; for (unsigned int i = 0; i < 152; i++) { if (i < value.length()) key38[i] = value[i]; else key38[i] = 0; }indexFunctions(index, key38, p); break;
            case 153: case 154: case 155: case 156: array<char, 156> key39; for (unsigned int i = 0; i < 156; i++) { if (i < value.length()) key39[i] = value[i]; else key39[i] = 0; }indexFunctions(index, key39, p); break;
            case 157: case 158: case 159: case 160: array<char, 160> key40; for (unsigned int i = 0; i < 160; i++) { if (i < value.length()) key40[i] = value[i]; else key40[i] = 0; }indexFunctions(index, key40, p); break;
            case 161: case 162: case 163: case 164: array<char, 164> key41; for (unsigned int i = 0; i < 164; i++) { if (i < value.length()) key41[i] = value[i]; else key41[i] = 0; }indexFunctions(index, key41, p); break;
            case 165: case 166: case 167: case 168: array<char, 168> key42; for (unsigned int i = 0; i < 168; i++) { if (i < value.length()) key42[i] = value[i]; else key42[i] = 0; }indexFunctions(index, key42, p); break;
            case 169: case 170: case 171: case 172: array<char, 172> key43; for (unsigned int i = 0; i < 172; i++) { if (i < value.length()) key43[i] = value[i]; else key43[i] = 0; }indexFunctions(index, key43, p); break;
            case 173: case 174: case 175: case 176: array<char, 176> key44; for (unsigned int i = 0; i < 176; i++) { if (i < value.length()) key44[i] = value[i]; else key44[i] = 0; }indexFunctions(index, key44, p); break;
            case 177: case 178: case 179: case 180: array<char, 180> key45; for (unsigned int i = 0; i < 180; i++) { if (i < value.length()) key45[i] = value[i]; else key45[i] = 0; }indexFunctions(index, key45, p); break;
            case 181: case 182: case 183: case 184: array<char, 184> key46; for (unsigned int i = 0; i < 184; i++) { if (i < value.length()) key46[i] = value[i]; else key46[i] = 0; }indexFunctions(index, key46, p); break;
            case 185: case 186: case 187: case 188: array<char, 188> key47; for (unsigned int i = 0; i < 188; i++) { if (i < value.length()) key47[i] = value[i]; else key47[i] = 0; }indexFunctions(index, key47, p); break;
            case 189: case 190: case 191: case 192: array<char, 192> key48; for (unsigned int i = 0; i < 192; i++) { if (i < value.length()) key48[i] = value[i]; else key48[i] = 0; }indexFunctions(index, key48, p); break;
            case 193: case 194: case 195: case 196: array<char, 196> key49; for (unsigned int i = 0; i < 196; i++) { if (i < value.length()) key49[i] = value[i]; else key49[i] = 0; }indexFunctions(index, key49, p); break;
            case 197: case 198: case 199: case 200: array<char, 200> key50; for (unsigned int i = 0; i < 200; i++) { if (i < value.length()) key50[i] = value[i]; else key50[i] = 0; }indexFunctions(index, key50, p); break;
            case 201: case 202: case 203: case 204: array<char, 204> key51; for (unsigned int i = 0; i < 204; i++) { if (i < value.length()) key51[i] = value[i]; else key51[i] = 0; }indexFunctions(index, key51, p); break;
            case 205: case 206: case 207: case 208: array<char, 208> key52; for (unsigned int i = 0; i < 208; i++) { if (i < value.length()) key52[i] = value[i]; else key52[i] = 0; }indexFunctions(index, key52, p); break;
            case 209: case 210: case 211: case 212: array<char, 212> key53; for (unsigned int i = 0; i < 212; i++) { if (i < value.length()) key53[i] = value[i]; else key53[i] = 0; }indexFunctions(index, key53, p); break;
            case 213: case 214: case 215: case 216: array<char, 216> key54; for (unsigned int i = 0; i < 216; i++) { if (i < value.length()) key54[i] = value[i]; else key54[i] = 0; }indexFunctions(index, key54, p); break;
            case 217: case 218: case 219: case 220: array<char, 220> key55; for (unsigned int i = 0; i < 220; i++) { if (i < value.length()) key55[i] = value[i]; else key55[i] = 0; }indexFunctions(index, key55, p); break;
            case 221: case 222: case 223: case 224: array<char, 224> key56; for (unsigned int i = 0; i < 224; i++) { if (i < value.length()) key56[i] = value[i]; else key56[i] = 0; }indexFunctions(index, key56, p); break;
            case 225: case 226: case 227: case 228: array<char, 228> key57; for (unsigned int i = 0; i < 228; i++) { if (i < value.length()) key57[i] = value[i]; else key57[i] = 0; }indexFunctions(index, key57, p); break;
            case 229: case 230: case 231: case 232: array<char, 232> key58; for (unsigned int i = 0; i < 232; i++) { if (i < value.length()) key58[i] = value[i]; else key58[i] = 0; }indexFunctions(index, key58, p); break;
            case 233: case 234: case 235: case 236: array<char, 236> key59; for (unsigned int i = 0; i < 236; i++) { if (i < value.length()) key59[i] = value[i]; else key59[i] = 0; }indexFunctions(index, key59, p); break;
            case 237: case 238: case 239: case 240: array<char, 240> key60; for (unsigned int i = 0; i < 240; i++) { if (i < value.length()) key60[i] = value[i]; else key60[i] = 0; }indexFunctions(index, key60, p); break;
            case 241: case 242: case 243: case 244: array<char, 244> key61; for (unsigned int i = 0; i < 244; i++) { if (i < value.length()) key61[i] = value[i]; else key61[i] = 0; }indexFunctions(index, key61, p); break;
            case 245: case 246: case 247: case 248: array<char, 248> key62; for (unsigned int i = 0; i < 248; i++) { if (i < value.length()) key62[i] = value[i]; else key62[i] = 0; }indexFunctions(index, key62, p); break;
            case 249: case 250: case 251: case 252: array<char, 252> key63; for (unsigned int i = 0; i < 252; i++) { if (i < value.length()) key63[i] = value[i]; else key63[i] = 0; }indexFunctions(index, key63, p); break;
            case 253: case 254: case 255: case 256:default: array<char, 256> key64; for (unsigned int i = 0; i < 256; i++) { if (i < value.length()) key64[i] = value[i]; else key64[i] = 0; }indexFunctions(index, key64, p); break;

            }
        }
    }
    vector<Index> getIndex(const string& tableName) {
        //return vector<Index>();//
        return catalog::getIndecies(tableName);
    }
    RecordPointer getPointerBetween(Index & index, const string & keyA, const string & keyB, bool withLeftBound, bool withRightBound) {
        switch (index.length) {
        case 1: case 2: case 3: case 4: array<char, 4> a1, b1; for (unsigned int i = 0; i<4; i++) { if (i < keyA.size()) { a1[i] = keyA[i]; } else { a1[i] = 0; }if (i < keyB.size()) { b1[i] = keyB[i]; } else { b1[i] = 0; } } return index::getPointerBetween(index, a1, b1, withLeftBound, withRightBound); break;
        case 5: case 6: case 7: case 8: array<char, 8> a2, b2; for (unsigned int i = 0; i<8; i++) { if (i < keyA.size()) { a2[i] = keyA[i]; } else { a2[i] = 0; }if (i < keyB.size()) { b2[i] = keyB[i]; } else { b2[i] = 0; } } return index::getPointerBetween(index, a2, b2, withLeftBound, withRightBound); break;
        case 9: case 10: case 11: case 12: array<char, 12> a3, b3; for (unsigned int i = 0; i<12; i++) { if (i < keyA.size()) { a3[i] = keyA[i]; } else { a3[i] = 0; }if (i < keyB.size()) { b3[i] = keyB[i]; } else { b3[i] = 0; } } return index::getPointerBetween(index, a3, b3, withLeftBound, withRightBound); break;
        case 13: case 14: case 15: case 16: array<char, 16> a4, b4; for (unsigned int i = 0; i<16; i++) { if (i < keyA.size()) { a4[i] = keyA[i]; } else { a4[i] = 0; }if (i < keyB.size()) { b4[i] = keyB[i]; } else { b4[i] = 0; } } return index::getPointerBetween(index, a4, b4, withLeftBound, withRightBound); break;
        case 17: case 18: case 19: case 20: array<char, 20> a5, b5; for (unsigned int i = 0; i<20; i++) { if (i < keyA.size()) { a5[i] = keyA[i]; } else { a5[i] = 0; }if (i < keyB.size()) { b5[i] = keyB[i]; } else { b5[i] = 0; } } return index::getPointerBetween(index, a5, b5, withLeftBound, withRightBound); break;
        case 21: case 22: case 23: case 24: array<char, 24> a6, b6; for (unsigned int i = 0; i<24; i++) { if (i < keyA.size()) { a6[i] = keyA[i]; } else { a6[i] = 0; }if (i < keyB.size()) { b6[i] = keyB[i]; } else { b6[i] = 0; } } return index::getPointerBetween(index, a6, b6, withLeftBound, withRightBound); break;
        case 25: case 26: case 27: case 28: array<char, 28> a7, b7; for (unsigned int i = 0; i<28; i++) { if (i < keyA.size()) { a7[i] = keyA[i]; } else { a7[i] = 0; }if (i < keyB.size()) { b7[i] = keyB[i]; } else { b7[i] = 0; } } return index::getPointerBetween(index, a7, b7, withLeftBound, withRightBound); break;
        case 29: case 30: case 31: case 32: array<char, 32> a8, b8; for (unsigned int i = 0; i<32; i++) { if (i < keyA.size()) { a8[i] = keyA[i]; } else { a8[i] = 0; }if (i < keyB.size()) { b8[i] = keyB[i]; } else { b8[i] = 0; } } return index::getPointerBetween(index, a8, b8, withLeftBound, withRightBound); break;
        case 33: case 34: case 35: case 36: array<char, 36> a9, b9; for (unsigned int i = 0; i<36; i++) { if (i < keyA.size()) { a9[i] = keyA[i]; } else { a9[i] = 0; }if (i < keyB.size()) { b9[i] = keyB[i]; } else { b9[i] = 0; } } return index::getPointerBetween(index, a9, b9, withLeftBound, withRightBound); break;
        case 37: case 38: case 39: case 40: array<char, 40> a10, b10; for (unsigned int i = 0; i<40; i++) { if (i < keyA.size()) { a10[i] = keyA[i]; } else { a10[i] = 0; }if (i < keyB.size()) { b10[i] = keyB[i]; } else { b10[i] = 0; } } return index::getPointerBetween(index, a10, b10, withLeftBound, withRightBound); break;
        case 41: case 42: case 43: case 44: array<char, 44> a11, b11; for (unsigned int i = 0; i<44; i++) { if (i < keyA.size()) { a11[i] = keyA[i]; } else { a11[i] = 0; }if (i < keyB.size()) { b11[i] = keyB[i]; } else { b11[i] = 0; } } return index::getPointerBetween(index, a11, b11, withLeftBound, withRightBound); break;
        case 45: case 46: case 47: case 48: array<char, 48> a12, b12; for (unsigned int i = 0; i<48; i++) { if (i < keyA.size()) { a12[i] = keyA[i]; } else { a12[i] = 0; }if (i < keyB.size()) { b12[i] = keyB[i]; } else { b12[i] = 0; } } return index::getPointerBetween(index, a12, b12, withLeftBound, withRightBound); break;
        case 49: case 50: case 51: case 52: array<char, 52> a13, b13; for (unsigned int i = 0; i<52; i++) { if (i < keyA.size()) { a13[i] = keyA[i]; } else { a13[i] = 0; }if (i < keyB.size()) { b13[i] = keyB[i]; } else { b13[i] = 0; } } return index::getPointerBetween(index, a13, b13, withLeftBound, withRightBound); break;
        case 53: case 54: case 55: case 56: array<char, 56> a14, b14; for (unsigned int i = 0; i<56; i++) { if (i < keyA.size()) { a14[i] = keyA[i]; } else { a14[i] = 0; }if (i < keyB.size()) { b14[i] = keyB[i]; } else { b14[i] = 0; } } return index::getPointerBetween(index, a14, b14, withLeftBound, withRightBound); break;
        case 57: case 58: case 59: case 60: array<char, 60> a15, b15; for (unsigned int i = 0; i<60; i++) { if (i < keyA.size()) { a15[i] = keyA[i]; } else { a15[i] = 0; }if (i < keyB.size()) { b15[i] = keyB[i]; } else { b15[i] = 0; } } return index::getPointerBetween(index, a15, b15, withLeftBound, withRightBound); break;
        case 61: case 62: case 63: case 64: array<char, 64> a16, b16; for (unsigned int i = 0; i<64; i++) { if (i < keyA.size()) { a16[i] = keyA[i]; } else { a16[i] = 0; }if (i < keyB.size()) { b16[i] = keyB[i]; } else { b16[i] = 0; } } return index::getPointerBetween(index, a16, b16, withLeftBound, withRightBound); break;
        case 65: case 66: case 67: case 68: array<char, 68> a17, b17; for (unsigned int i = 0; i<68; i++) { if (i < keyA.size()) { a17[i] = keyA[i]; } else { a17[i] = 0; }if (i < keyB.size()) { b17[i] = keyB[i]; } else { b17[i] = 0; } } return index::getPointerBetween(index, a17, b17, withLeftBound, withRightBound); break;
        case 69: case 70: case 71: case 72: array<char, 72> a18, b18; for (unsigned int i = 0; i<72; i++) { if (i < keyA.size()) { a18[i] = keyA[i]; } else { a18[i] = 0; }if (i < keyB.size()) { b18[i] = keyB[i]; } else { b18[i] = 0; } } return index::getPointerBetween(index, a18, b18, withLeftBound, withRightBound); break;
        case 73: case 74: case 75: case 76: array<char, 76> a19, b19; for (unsigned int i = 0; i<76; i++) { if (i < keyA.size()) { a19[i] = keyA[i]; } else { a19[i] = 0; }if (i < keyB.size()) { b19[i] = keyB[i]; } else { b19[i] = 0; } } return index::getPointerBetween(index, a19, b19, withLeftBound, withRightBound); break;
        case 77: case 78: case 79: case 80: array<char, 80> a20, b20; for (unsigned int i = 0; i<80; i++) { if (i < keyA.size()) { a20[i] = keyA[i]; } else { a20[i] = 0; }if (i < keyB.size()) { b20[i] = keyB[i]; } else { b20[i] = 0; } } return index::getPointerBetween(index, a20, b20, withLeftBound, withRightBound); break;
        case 81: case 82: case 83: case 84: array<char, 84> a21, b21; for (unsigned int i = 0; i<84; i++) { if (i < keyA.size()) { a21[i] = keyA[i]; } else { a21[i] = 0; }if (i < keyB.size()) { b21[i] = keyB[i]; } else { b21[i] = 0; } } return index::getPointerBetween(index, a21, b21, withLeftBound, withRightBound); break;
        case 85: case 86: case 87: case 88: array<char, 88> a22, b22; for (unsigned int i = 0; i<88; i++) { if (i < keyA.size()) { a22[i] = keyA[i]; } else { a22[i] = 0; }if (i < keyB.size()) { b22[i] = keyB[i]; } else { b22[i] = 0; } } return index::getPointerBetween(index, a22, b22, withLeftBound, withRightBound); break;
        case 89: case 90: case 91: case 92: array<char, 92> a23, b23; for (unsigned int i = 0; i<92; i++) { if (i < keyA.size()) { a23[i] = keyA[i]; } else { a23[i] = 0; }if (i < keyB.size()) { b23[i] = keyB[i]; } else { b23[i] = 0; } } return index::getPointerBetween(index, a23, b23, withLeftBound, withRightBound); break;
        case 93: case 94: case 95: case 96: array<char, 96> a24, b24; for (unsigned int i = 0; i<96; i++) { if (i < keyA.size()) { a24[i] = keyA[i]; } else { a24[i] = 0; }if (i < keyB.size()) { b24[i] = keyB[i]; } else { b24[i] = 0; } } return index::getPointerBetween(index, a24, b24, withLeftBound, withRightBound); break;
        case 97: case 98: case 99: case 100: array<char, 100> a25, b25; for (unsigned int i = 0; i<100; i++) { if (i < keyA.size()) { a25[i] = keyA[i]; } else { a25[i] = 0; }if (i < keyB.size()) { b25[i] = keyB[i]; } else { b25[i] = 0; } } return index::getPointerBetween(index, a25, b25, withLeftBound, withRightBound); break;
        case 101: case 102: case 103: case 104: array<char, 104> a26, b26; for (unsigned int i = 0; i<104; i++) { if (i < keyA.size()) { a26[i] = keyA[i]; } else { a26[i] = 0; }if (i < keyB.size()) { b26[i] = keyB[i]; } else { b26[i] = 0; } } return index::getPointerBetween(index, a26, b26, withLeftBound, withRightBound); break;
        case 105: case 106: case 107: case 108: array<char, 108> a27, b27; for (unsigned int i = 0; i<108; i++) { if (i < keyA.size()) { a27[i] = keyA[i]; } else { a27[i] = 0; }if (i < keyB.size()) { b27[i] = keyB[i]; } else { b27[i] = 0; } } return index::getPointerBetween(index, a27, b27, withLeftBound, withRightBound); break;
        case 109: case 110: case 111: case 112: array<char, 112> a28, b28; for (unsigned int i = 0; i<112; i++) { if (i < keyA.size()) { a28[i] = keyA[i]; } else { a28[i] = 0; }if (i < keyB.size()) { b28[i] = keyB[i]; } else { b28[i] = 0; } } return index::getPointerBetween(index, a28, b28, withLeftBound, withRightBound); break;
        case 113: case 114: case 115: case 116: array<char, 116> a29, b29; for (unsigned int i = 0; i<116; i++) { if (i < keyA.size()) { a29[i] = keyA[i]; } else { a29[i] = 0; }if (i < keyB.size()) { b29[i] = keyB[i]; } else { b29[i] = 0; } } return index::getPointerBetween(index, a29, b29, withLeftBound, withRightBound); break;
        case 117: case 118: case 119: case 120: array<char, 120> a30, b30; for (unsigned int i = 0; i<120; i++) { if (i < keyA.size()) { a30[i] = keyA[i]; } else { a30[i] = 0; }if (i < keyB.size()) { b30[i] = keyB[i]; } else { b30[i] = 0; } } return index::getPointerBetween(index, a30, b30, withLeftBound, withRightBound); break;
        case 121: case 122: case 123: case 124: array<char, 124> a31, b31; for (unsigned int i = 0; i<124; i++) { if (i < keyA.size()) { a31[i] = keyA[i]; } else { a31[i] = 0; }if (i < keyB.size()) { b31[i] = keyB[i]; } else { b31[i] = 0; } } return index::getPointerBetween(index, a31, b31, withLeftBound, withRightBound); break;
        case 125: case 126: case 127: case 128: array<char, 128> a32, b32; for (unsigned int i = 0; i<128; i++) { if (i < keyA.size()) { a32[i] = keyA[i]; } else { a32[i] = 0; }if (i < keyB.size()) { b32[i] = keyB[i]; } else { b32[i] = 0; } } return index::getPointerBetween(index, a32, b32, withLeftBound, withRightBound); break;
        case 129: case 130: case 131: case 132: array<char, 132> a33, b33; for (unsigned int i = 0; i<132; i++) { if (i < keyA.size()) { a33[i] = keyA[i]; } else { a33[i] = 0; }if (i < keyB.size()) { b33[i] = keyB[i]; } else { b33[i] = 0; } } return index::getPointerBetween(index, a33, b33, withLeftBound, withRightBound); break;
        case 133: case 134: case 135: case 136: array<char, 136> a34, b34; for (unsigned int i = 0; i<136; i++) { if (i < keyA.size()) { a34[i] = keyA[i]; } else { a34[i] = 0; }if (i < keyB.size()) { b34[i] = keyB[i]; } else { b34[i] = 0; } } return index::getPointerBetween(index, a34, b34, withLeftBound, withRightBound); break;
        case 137: case 138: case 139: case 140: array<char, 140> a35, b35; for (unsigned int i = 0; i<140; i++) { if (i < keyA.size()) { a35[i] = keyA[i]; } else { a35[i] = 0; }if (i < keyB.size()) { b35[i] = keyB[i]; } else { b35[i] = 0; } } return index::getPointerBetween(index, a35, b35, withLeftBound, withRightBound); break;
        case 141: case 142: case 143: case 144: array<char, 144> a36, b36; for (unsigned int i = 0; i<144; i++) { if (i < keyA.size()) { a36[i] = keyA[i]; } else { a36[i] = 0; }if (i < keyB.size()) { b36[i] = keyB[i]; } else { b36[i] = 0; } } return index::getPointerBetween(index, a36, b36, withLeftBound, withRightBound); break;
        case 145: case 146: case 147: case 148: array<char, 148> a37, b37; for (unsigned int i = 0; i<148; i++) { if (i < keyA.size()) { a37[i] = keyA[i]; } else { a37[i] = 0; }if (i < keyB.size()) { b37[i] = keyB[i]; } else { b37[i] = 0; } } return index::getPointerBetween(index, a37, b37, withLeftBound, withRightBound); break;
        case 149: case 150: case 151: case 152: array<char, 152> a38, b38; for (unsigned int i = 0; i<152; i++) { if (i < keyA.size()) { a38[i] = keyA[i]; } else { a38[i] = 0; }if (i < keyB.size()) { b38[i] = keyB[i]; } else { b38[i] = 0; } } return index::getPointerBetween(index, a38, b38, withLeftBound, withRightBound); break;
        case 153: case 154: case 155: case 156: array<char, 156> a39, b39; for (unsigned int i = 0; i<156; i++) { if (i < keyA.size()) { a39[i] = keyA[i]; } else { a39[i] = 0; }if (i < keyB.size()) { b39[i] = keyB[i]; } else { b39[i] = 0; } } return index::getPointerBetween(index, a39, b39, withLeftBound, withRightBound); break;
        case 157: case 158: case 159: case 160: array<char, 160> a40, b40; for (unsigned int i = 0; i<160; i++) { if (i < keyA.size()) { a40[i] = keyA[i]; } else { a40[i] = 0; }if (i < keyB.size()) { b40[i] = keyB[i]; } else { b40[i] = 0; } } return index::getPointerBetween(index, a40, b40, withLeftBound, withRightBound); break;
        case 161: case 162: case 163: case 164: array<char, 164> a41, b41; for (unsigned int i = 0; i<164; i++) { if (i < keyA.size()) { a41[i] = keyA[i]; } else { a41[i] = 0; }if (i < keyB.size()) { b41[i] = keyB[i]; } else { b41[i] = 0; } } return index::getPointerBetween(index, a41, b41, withLeftBound, withRightBound); break;
        case 165: case 166: case 167: case 168: array<char, 168> a42, b42; for (unsigned int i = 0; i<168; i++) { if (i < keyA.size()) { a42[i] = keyA[i]; } else { a42[i] = 0; }if (i < keyB.size()) { b42[i] = keyB[i]; } else { b42[i] = 0; } } return index::getPointerBetween(index, a42, b42, withLeftBound, withRightBound); break;
        case 169: case 170: case 171: case 172: array<char, 172> a43, b43; for (unsigned int i = 0; i<172; i++) { if (i < keyA.size()) { a43[i] = keyA[i]; } else { a43[i] = 0; }if (i < keyB.size()) { b43[i] = keyB[i]; } else { b43[i] = 0; } } return index::getPointerBetween(index, a43, b43, withLeftBound, withRightBound); break;
        case 173: case 174: case 175: case 176: array<char, 176> a44, b44; for (unsigned int i = 0; i<176; i++) { if (i < keyA.size()) { a44[i] = keyA[i]; } else { a44[i] = 0; }if (i < keyB.size()) { b44[i] = keyB[i]; } else { b44[i] = 0; } } return index::getPointerBetween(index, a44, b44, withLeftBound, withRightBound); break;
        case 177: case 178: case 179: case 180: array<char, 180> a45, b45; for (unsigned int i = 0; i<180; i++) { if (i < keyA.size()) { a45[i] = keyA[i]; } else { a45[i] = 0; }if (i < keyB.size()) { b45[i] = keyB[i]; } else { b45[i] = 0; } } return index::getPointerBetween(index, a45, b45, withLeftBound, withRightBound); break;
        case 181: case 182: case 183: case 184: array<char, 184> a46, b46; for (unsigned int i = 0; i<184; i++) { if (i < keyA.size()) { a46[i] = keyA[i]; } else { a46[i] = 0; }if (i < keyB.size()) { b46[i] = keyB[i]; } else { b46[i] = 0; } } return index::getPointerBetween(index, a46, b46, withLeftBound, withRightBound); break;
        case 185: case 186: case 187: case 188: array<char, 188> a47, b47; for (unsigned int i = 0; i<188; i++) { if (i < keyA.size()) { a47[i] = keyA[i]; } else { a47[i] = 0; }if (i < keyB.size()) { b47[i] = keyB[i]; } else { b47[i] = 0; } } return index::getPointerBetween(index, a47, b47, withLeftBound, withRightBound); break;
        case 189: case 190: case 191: case 192: array<char, 192> a48, b48; for (unsigned int i = 0; i<192; i++) { if (i < keyA.size()) { a48[i] = keyA[i]; } else { a48[i] = 0; }if (i < keyB.size()) { b48[i] = keyB[i]; } else { b48[i] = 0; } } return index::getPointerBetween(index, a48, b48, withLeftBound, withRightBound); break;
        case 193: case 194: case 195: case 196: array<char, 196> a49, b49; for (unsigned int i = 0; i<196; i++) { if (i < keyA.size()) { a49[i] = keyA[i]; } else { a49[i] = 0; }if (i < keyB.size()) { b49[i] = keyB[i]; } else { b49[i] = 0; } } return index::getPointerBetween(index, a49, b49, withLeftBound, withRightBound); break;
        case 197: case 198: case 199: case 200: array<char, 200> a50, b50; for (unsigned int i = 0; i<200; i++) { if (i < keyA.size()) { a50[i] = keyA[i]; } else { a50[i] = 0; }if (i < keyB.size()) { b50[i] = keyB[i]; } else { b50[i] = 0; } } return index::getPointerBetween(index, a50, b50, withLeftBound, withRightBound); break;
        case 201: case 202: case 203: case 204: array<char, 204> a51, b51; for (unsigned int i = 0; i<204; i++) { if (i < keyA.size()) { a51[i] = keyA[i]; } else { a51[i] = 0; }if (i < keyB.size()) { b51[i] = keyB[i]; } else { b51[i] = 0; } } return index::getPointerBetween(index, a51, b51, withLeftBound, withRightBound); break;
        case 205: case 206: case 207: case 208: array<char, 208> a52, b52; for (unsigned int i = 0; i<208; i++) { if (i < keyA.size()) { a52[i] = keyA[i]; } else { a52[i] = 0; }if (i < keyB.size()) { b52[i] = keyB[i]; } else { b52[i] = 0; } } return index::getPointerBetween(index, a52, b52, withLeftBound, withRightBound); break;
        case 209: case 210: case 211: case 212: array<char, 212> a53, b53; for (unsigned int i = 0; i<212; i++) { if (i < keyA.size()) { a53[i] = keyA[i]; } else { a53[i] = 0; }if (i < keyB.size()) { b53[i] = keyB[i]; } else { b53[i] = 0; } } return index::getPointerBetween(index, a53, b53, withLeftBound, withRightBound); break;
        case 213: case 214: case 215: case 216: array<char, 216> a54, b54; for (unsigned int i = 0; i<216; i++) { if (i < keyA.size()) { a54[i] = keyA[i]; } else { a54[i] = 0; }if (i < keyB.size()) { b54[i] = keyB[i]; } else { b54[i] = 0; } } return index::getPointerBetween(index, a54, b54, withLeftBound, withRightBound); break;
        case 217: case 218: case 219: case 220: array<char, 220> a55, b55; for (unsigned int i = 0; i<220; i++) { if (i < keyA.size()) { a55[i] = keyA[i]; } else { a55[i] = 0; }if (i < keyB.size()) { b55[i] = keyB[i]; } else { b55[i] = 0; } } return index::getPointerBetween(index, a55, b55, withLeftBound, withRightBound); break;
        case 221: case 222: case 223: case 224: array<char, 224> a56, b56; for (unsigned int i = 0; i<224; i++) { if (i < keyA.size()) { a56[i] = keyA[i]; } else { a56[i] = 0; }if (i < keyB.size()) { b56[i] = keyB[i]; } else { b56[i] = 0; } } return index::getPointerBetween(index, a56, b56, withLeftBound, withRightBound); break;
        case 225: case 226: case 227: case 228: array<char, 228> a57, b57; for (unsigned int i = 0; i<228; i++) { if (i < keyA.size()) { a57[i] = keyA[i]; } else { a57[i] = 0; }if (i < keyB.size()) { b57[i] = keyB[i]; } else { b57[i] = 0; } } return index::getPointerBetween(index, a57, b57, withLeftBound, withRightBound); break;
        case 229: case 230: case 231: case 232: array<char, 232> a58, b58; for (unsigned int i = 0; i<232; i++) { if (i < keyA.size()) { a58[i] = keyA[i]; } else { a58[i] = 0; }if (i < keyB.size()) { b58[i] = keyB[i]; } else { b58[i] = 0; } } return index::getPointerBetween(index, a58, b58, withLeftBound, withRightBound); break;
        case 233: case 234: case 235: case 236: array<char, 236> a59, b59; for (unsigned int i = 0; i<236; i++) { if (i < keyA.size()) { a59[i] = keyA[i]; } else { a59[i] = 0; }if (i < keyB.size()) { b59[i] = keyB[i]; } else { b59[i] = 0; } } return index::getPointerBetween(index, a59, b59, withLeftBound, withRightBound); break;
        case 237: case 238: case 239: case 240: array<char, 240> a60, b60; for (unsigned int i = 0; i<240; i++) { if (i < keyA.size()) { a60[i] = keyA[i]; } else { a60[i] = 0; }if (i < keyB.size()) { b60[i] = keyB[i]; } else { b60[i] = 0; } } return index::getPointerBetween(index, a60, b60, withLeftBound, withRightBound); break;
        case 241: case 242: case 243: case 244: array<char, 244> a61, b61; for (unsigned int i = 0; i<244; i++) { if (i < keyA.size()) { a61[i] = keyA[i]; } else { a61[i] = 0; }if (i < keyB.size()) { b61[i] = keyB[i]; } else { b61[i] = 0; } } return index::getPointerBetween(index, a61, b61, withLeftBound, withRightBound); break;
        case 245: case 246: case 247: case 248: array<char, 248> a62, b62; for (unsigned int i = 0; i<248; i++) { if (i < keyA.size()) { a62[i] = keyA[i]; } else { a62[i] = 0; }if (i < keyB.size()) { b62[i] = keyB[i]; } else { b62[i] = 0; } } return index::getPointerBetween(index, a62, b62, withLeftBound, withRightBound); break;
        case 249: case 250: case 251: case 252: array<char, 252> a63, b63; for (unsigned int i = 0; i<252; i++) { if (i < keyA.size()) { a63[i] = keyA[i]; } else { a63[i] = 0; }if (i < keyB.size()) { b63[i] = keyB[i]; } else { b63[i] = 0; } } return index::getPointerBetween(index, a63, b63, withLeftBound, withRightBound); break;
        default:case 253: case 254: case 255: case 256: array<char, 256> a64, b64; for (unsigned int i = 0; i<256; i++) { if (i < keyA.size()) { a64[i] = keyA[i]; } else { a64[i] = 0; }if (i < keyB.size()) { b64[i] = keyB[i]; } else { b64[i] = 0; } } return index::getPointerBetween(index, a64, b64, withLeftBound, withRightBound); break;


        }
    }
    RecordPointer getPointerBetween(Index & index, const int & keyA, const int & keyB, bool withLeftBound, bool withRightBound) {
        array<int, 1> a, b;
        a[0] = keyA;
        b[0] = keyB;
        return index::getPointerBetween(index, a, b, withLeftBound, withRightBound);
    }
    RecordPointer getPointerBetween(Index & index, const float & keyA, const float & keyB, bool withLeftBound, bool withRightBound) {
        array<float, 1> a, b;
        a[0] = keyA;
        b[0] = keyB;
        return index::getPointerBetween(index, a, b, withLeftBound, withRightBound);
    }
    void createTable(const string& tableName, const vector<AttributeConstraint>& attributes) {
        Table table(tableName);
        table.attrList = attributes;
        if (!catalog::createTable(table)) {
            throw(MyException("creat catalog on \"" + tableName + "\" failed\n"));
        }
        RecordManager::createTable(tableName);
        for (auto& attr : attributes) {
            if (attr.isPrimaryKey()) {
                Index index(tableName + "_" + attr.getColumnName(), tableName, attr.getColumnName(), attr.getType(), attr.getLength());
                if (!catalog::createIndex(index))throw MyException("create index log failed\n");
                if (!index::createIndex(index))throw MyException("create index file failed\n");
            }
        }
    }

    void createIndex(const string& tableName, const string& indexName, const string& attributeName) {
        Table table;
        Index index(indexName, tableName, attributeName);
        vector<RecordPointer> pointerList;
        vector<string> nameList, dataList;
        ResultSet result;
        unsigned int no, count = 0;
        table = catalog::getTable(tableName);
        for (auto& attr : table.attrList) {
            if (attr.getColumnName() == attributeName) {
                if (!attr.isUnique()) {
                    throw MyException("create index failed: \"" + attributeName + "\" isn't unique\n");
                }
                index.length = attr.getLength();
                index.type = attr.getType();
            }
        }
        if (!catalog::createIndex(index))throw MyException("log index failed\n");
        if (!index::createIndex(index))throw MyException("create index file failed\n");
        result = RecordManager::search(table, vector<Clause>(), pointerList);
        nameList = result.getColumnNames();
        for (no = 0; no < nameList.size(); no++) {
            if (nameList[no] == attributeName) {
                break;
            }
        }
        if (no == nameList.size())throw MyException("create index failed: \"" + attributeName + "\" doesn't exist on \"" + tableName + "\"\n");
        while (result.next()) {
            indexFuns(index, result.getData()[no], index::rtop(pointerList[count++]));
        }
    }

    void dropTable(const string& tableName) {
        vector<Index> indexList = catalog::getIndecies(tableName);
        for (auto&index : indexList) {
            if (!index::dropIndex(index.name))throw MyException("drop index file failed\n");
        }
        RecordManager::dropTable(tableName);
        if (!catalog::dropTable(tableName))throw MyException("drop table log failed\n");
    }

    void dropIndex(const string& indexName) {
        if (!index::dropIndex(indexName))throw MyException("drop index file failed\n");
        if (!catalog::dropIndex(indexName))throw MyException("drop index log failed\n");
    }

    void insertTuple(const string& tableName, vector<string>& values) {
        Table& table = catalog::getTable(tableName);
        vector<Index>& indexList = catalog::getIndecies(tableName);
        for (auto&index : indexList) {
            for (unsigned int i = 0; i < table.attrList.size(); i++) {
                if (index.attr == table.attrList[i].getColumnName()) {
                    indexFuns(index, values[i], index::rtop(table.end));
                    //index.writeBack();
                }
            }
        }
        RecordManager::Insert(table, values);
        table.end.next(RecordManager::getSize(table.attrList), 4096);
        //table.writeBack();
    }

    void deleteTuple(const string& tableName, vector<Clause>& clauses) {
        Table table = catalog::getTable(tableName);
        vector<Index> indexList = catalog::getIndecies(tableName);
        ResultSet res = RecordManager::deleteFrom(table, clauses);
        while (res.next()) {
            for (auto&index : indexList) {
                for (unsigned int i = 0; i < table.attrList.size(); i++) {
                    if (index.attr == table.attrList[i].getColumnName()) {
                        indexFuns(index, res.getData()[i]);
                    }
                }
            }
        }
    }

    void quit() {
        BufferManager::clear();
        for (auto&table : catalog::tables) {
            table.second.writeBack();
        }
        for (auto&vindex : catalog::ioft) {
            for (auto&index : vindex.second) {
                index.writeBack();
            }
        }
    }

    ResultSet search(const string& tableName, vector<Clause>& clauses) {
        Table table = catalog::getTable(tableName);
        return RecordManager::search(table, clauses);
    }
}