#include "index.h"
namespace index {

    bool createIndex(const Index& index) {
        try {
            BufferManager::createIndexFile(index.name);
        } catch (...) {
            cerr << "createIndex failed\n";
            return false;
        }
        return true;
    }
    bool dropIndex(const string& indexName) {
        try {
            BufferManager::deleteFile(indexName, "index");
        } catch (...) {
            cerr << "dropIndex failed\n";
            return false;
        }
        return true;
    }
    bool insertTuple(const Table& table, const vector<string>& values, const RecordPointer& p) {
        bool flag = false;
        for (auto& index : catalog::getIndecies(table.name)) {
            for (unsigned int i = 0; i < table.attrList.size(); i++) {
                if (table.attrList[i].getColumnName() == index.attr) {
                    if (insertIndex(index, table.attrList[i], values[i], rtop(p))) {
                        flag = true;
                    }
                }
            }
        }
        return flag;
    }
    bool insertIndex(Index& index, const AttributeConstraint& attr, const string& value, const Pointer& p) {
        try {
            if (attr.getType() == "INT") {
                array<int, 1> key;
                key[0] = stoi(value);
                insertIndex(index, key, p);
            } else if (attr.getType() == "FLOAT") {
                array<float, 1> key;
                key[0] = stof(value);
                insertIndex(index, key, p);
            } else {
                switch (attr.getLength()) {
                case 1: case 2: case 3: case 4: array<char, 4> key1; for (unsigned int i = 0; i < 4; i++) { if (i < value.length()) key1[i] = value[i]; else key1[i] = 0; }insertIndex(index, key1, p); break;
                case 5: case 6: case 7: case 8: array<char, 8> key2; for (unsigned int i = 0; i < 8; i++) { if (i < value.length()) key2[i] = value[i]; else key2[i] = 0; }insertIndex(index, key2, p); break;
                case 9: case 10: case 11: case 12: array<char, 12> key3; for (unsigned int i = 0; i < 12; i++) { if (i < value.length()) key3[i] = value[i]; else key3[i] = 0; }insertIndex(index, key3, p); break;
                case 13: case 14: case 15: case 16: array<char, 16> key4; for (unsigned int i = 0; i < 16; i++) { if (i < value.length()) key4[i] = value[i]; else key4[i] = 0; }insertIndex(index, key4, p); break;
                case 17: case 18: case 19: case 20: array<char, 20> key5; for (unsigned int i = 0; i < 20; i++) { if (i < value.length()) key5[i] = value[i]; else key5[i] = 0; }insertIndex(index, key5, p); break;
                case 21: case 22: case 23: case 24: array<char, 24> key6; for (unsigned int i = 0; i < 24; i++) { if (i < value.length()) key6[i] = value[i]; else key6[i] = 0; }insertIndex(index, key6, p); break;
                case 25: case 26: case 27: case 28: array<char, 28> key7; for (unsigned int i = 0; i < 28; i++) { if (i < value.length()) key7[i] = value[i]; else key7[i] = 0; }insertIndex(index, key7, p); break;
                case 29: case 30: case 31: case 32: array<char, 32> key8; for (unsigned int i = 0; i < 32; i++) { if (i < value.length()) key8[i] = value[i]; else key8[i] = 0; }insertIndex(index, key8, p); break;
                case 33: case 34: case 35: case 36: array<char, 36> key9; for (unsigned int i = 0; i < 36; i++) { if (i < value.length()) key9[i] = value[i]; else key9[i] = 0; }insertIndex(index, key9, p); break;
                case 37: case 38: case 39: case 40: array<char, 40> key10; for (unsigned int i = 0; i < 40; i++) { if (i < value.length()) key10[i] = value[i]; else key10[i] = 0; }insertIndex(index, key10, p); break;
                case 41: case 42: case 43: case 44: array<char, 44> key11; for (unsigned int i = 0; i < 44; i++) { if (i < value.length()) key11[i] = value[i]; else key11[i] = 0; }insertIndex(index, key11, p); break;
                case 45: case 46: case 47: case 48: array<char, 48> key12; for (unsigned int i = 0; i < 48; i++) { if (i < value.length()) key12[i] = value[i]; else key12[i] = 0; }insertIndex(index, key12, p); break;
                case 49: case 50: case 51: case 52: array<char, 52> key13; for (unsigned int i = 0; i < 52; i++) { if (i < value.length()) key13[i] = value[i]; else key13[i] = 0; }insertIndex(index, key13, p); break;
                case 53: case 54: case 55: case 56: array<char, 56> key14; for (unsigned int i = 0; i < 56; i++) { if (i < value.length()) key14[i] = value[i]; else key14[i] = 0; }insertIndex(index, key14, p); break;
                case 57: case 58: case 59: case 60: array<char, 60> key15; for (unsigned int i = 0; i < 60; i++) { if (i < value.length()) key15[i] = value[i]; else key15[i] = 0; }insertIndex(index, key15, p); break;
                case 61: case 62: case 63: case 64: array<char, 64> key16; for (unsigned int i = 0; i < 64; i++) { if (i < value.length()) key16[i] = value[i]; else key16[i] = 0; }insertIndex(index, key16, p); break;
                case 65: case 66: case 67: case 68: array<char, 68> key17; for (unsigned int i = 0; i < 68; i++) { if (i < value.length()) key17[i] = value[i]; else key17[i] = 0; }insertIndex(index, key17, p); break;
                case 69: case 70: case 71: case 72: array<char, 72> key18; for (unsigned int i = 0; i < 72; i++) { if (i < value.length()) key18[i] = value[i]; else key18[i] = 0; }insertIndex(index, key18, p); break;
                case 73: case 74: case 75: case 76: array<char, 76> key19; for (unsigned int i = 0; i < 76; i++) { if (i < value.length()) key19[i] = value[i]; else key19[i] = 0; }insertIndex(index, key19, p); break;
                case 77: case 78: case 79: case 80: array<char, 80> key20; for (unsigned int i = 0; i < 80; i++) { if (i < value.length()) key20[i] = value[i]; else key20[i] = 0; }insertIndex(index, key20, p); break;
                case 81: case 82: case 83: case 84: array<char, 84> key21; for (unsigned int i = 0; i < 84; i++) { if (i < value.length()) key21[i] = value[i]; else key21[i] = 0; }insertIndex(index, key21, p); break;
                case 85: case 86: case 87: case 88: array<char, 88> key22; for (unsigned int i = 0; i < 88; i++) { if (i < value.length()) key22[i] = value[i]; else key22[i] = 0; }insertIndex(index, key22, p); break;
                case 89: case 90: case 91: case 92: array<char, 92> key23; for (unsigned int i = 0; i < 92; i++) { if (i < value.length()) key23[i] = value[i]; else key23[i] = 0; }insertIndex(index, key23, p); break;
                case 93: case 94: case 95: case 96: array<char, 96> key24; for (unsigned int i = 0; i < 96; i++) { if (i < value.length()) key24[i] = value[i]; else key24[i] = 0; }insertIndex(index, key24, p); break;
                case 97: case 98: case 99: case 100: array<char, 100> key25; for (unsigned int i = 0; i < 100; i++) { if (i < value.length()) key25[i] = value[i]; else key25[i] = 0; }insertIndex(index, key25, p); break;
                case 101: case 102: case 103: case 104: array<char, 104> key26; for (unsigned int i = 0; i < 104; i++) { if (i < value.length()) key26[i] = value[i]; else key26[i] = 0; }insertIndex(index, key26, p); break;
                case 105: case 106: case 107: case 108: array<char, 108> key27; for (unsigned int i = 0; i < 108; i++) { if (i < value.length()) key27[i] = value[i]; else key27[i] = 0; }insertIndex(index, key27, p); break;
                case 109: case 110: case 111: case 112: array<char, 112> key28; for (unsigned int i = 0; i < 112; i++) { if (i < value.length()) key28[i] = value[i]; else key28[i] = 0; }insertIndex(index, key28, p); break;
                case 113: case 114: case 115: case 116: array<char, 116> key29; for (unsigned int i = 0; i < 116; i++) { if (i < value.length()) key29[i] = value[i]; else key29[i] = 0; }insertIndex(index, key29, p); break;
                case 117: case 118: case 119: case 120: array<char, 120> key30; for (unsigned int i = 0; i < 120; i++) { if (i < value.length()) key30[i] = value[i]; else key30[i] = 0; }insertIndex(index, key30, p); break;
                case 121: case 122: case 123: case 124: array<char, 124> key31; for (unsigned int i = 0; i < 124; i++) { if (i < value.length()) key31[i] = value[i]; else key31[i] = 0; }insertIndex(index, key31, p); break;
                case 125: case 126: case 127: case 128: array<char, 128> key32; for (unsigned int i = 0; i < 128; i++) { if (i < value.length()) key32[i] = value[i]; else key32[i] = 0; }insertIndex(index, key32, p); break;
                case 129: case 130: case 131: case 132: array<char, 132> key33; for (unsigned int i = 0; i < 132; i++) { if (i < value.length()) key33[i] = value[i]; else key33[i] = 0; }insertIndex(index, key33, p); break;
                case 133: case 134: case 135: case 136: array<char, 136> key34; for (unsigned int i = 0; i < 136; i++) { if (i < value.length()) key34[i] = value[i]; else key34[i] = 0; }insertIndex(index, key34, p); break;
                case 137: case 138: case 139: case 140: array<char, 140> key35; for (unsigned int i = 0; i < 140; i++) { if (i < value.length()) key35[i] = value[i]; else key35[i] = 0; }insertIndex(index, key35, p); break;
                case 141: case 142: case 143: case 144: array<char, 144> key36; for (unsigned int i = 0; i < 144; i++) { if (i < value.length()) key36[i] = value[i]; else key36[i] = 0; }insertIndex(index, key36, p); break;
                case 145: case 146: case 147: case 148: array<char, 148> key37; for (unsigned int i = 0; i < 148; i++) { if (i < value.length()) key37[i] = value[i]; else key37[i] = 0; }insertIndex(index, key37, p); break;
                case 149: case 150: case 151: case 152: array<char, 152> key38; for (unsigned int i = 0; i < 152; i++) { if (i < value.length()) key38[i] = value[i]; else key38[i] = 0; }insertIndex(index, key38, p); break;
                case 153: case 154: case 155: case 156: array<char, 156> key39; for (unsigned int i = 0; i < 156; i++) { if (i < value.length()) key39[i] = value[i]; else key39[i] = 0; }insertIndex(index, key39, p); break;
                case 157: case 158: case 159: case 160: array<char, 160> key40; for (unsigned int i = 0; i < 160; i++) { if (i < value.length()) key40[i] = value[i]; else key40[i] = 0; }insertIndex(index, key40, p); break;
                case 161: case 162: case 163: case 164: array<char, 164> key41; for (unsigned int i = 0; i < 164; i++) { if (i < value.length()) key41[i] = value[i]; else key41[i] = 0; }insertIndex(index, key41, p); break;
                case 165: case 166: case 167: case 168: array<char, 168> key42; for (unsigned int i = 0; i < 168; i++) { if (i < value.length()) key42[i] = value[i]; else key42[i] = 0; }insertIndex(index, key42, p); break;
                case 169: case 170: case 171: case 172: array<char, 172> key43; for (unsigned int i = 0; i < 172; i++) { if (i < value.length()) key43[i] = value[i]; else key43[i] = 0; }insertIndex(index, key43, p); break;
                case 173: case 174: case 175: case 176: array<char, 176> key44; for (unsigned int i = 0; i < 176; i++) { if (i < value.length()) key44[i] = value[i]; else key44[i] = 0; }insertIndex(index, key44, p); break;
                case 177: case 178: case 179: case 180: array<char, 180> key45; for (unsigned int i = 0; i < 180; i++) { if (i < value.length()) key45[i] = value[i]; else key45[i] = 0; }insertIndex(index, key45, p); break;
                case 181: case 182: case 183: case 184: array<char, 184> key46; for (unsigned int i = 0; i < 184; i++) { if (i < value.length()) key46[i] = value[i]; else key46[i] = 0; }insertIndex(index, key46, p); break;
                case 185: case 186: case 187: case 188: array<char, 188> key47; for (unsigned int i = 0; i < 188; i++) { if (i < value.length()) key47[i] = value[i]; else key47[i] = 0; }insertIndex(index, key47, p); break;
                case 189: case 190: case 191: case 192: array<char, 192> key48; for (unsigned int i = 0; i < 192; i++) { if (i < value.length()) key48[i] = value[i]; else key48[i] = 0; }insertIndex(index, key48, p); break;
                case 193: case 194: case 195: case 196: array<char, 196> key49; for (unsigned int i = 0; i < 196; i++) { if (i < value.length()) key49[i] = value[i]; else key49[i] = 0; }insertIndex(index, key49, p); break;
                case 197: case 198: case 199: case 200: array<char, 200> key50; for (unsigned int i = 0; i < 200; i++) { if (i < value.length()) key50[i] = value[i]; else key50[i] = 0; }insertIndex(index, key50, p); break;
                case 201: case 202: case 203: case 204: array<char, 204> key51; for (unsigned int i = 0; i < 204; i++) { if (i < value.length()) key51[i] = value[i]; else key51[i] = 0; }insertIndex(index, key51, p); break;
                case 205: case 206: case 207: case 208: array<char, 208> key52; for (unsigned int i = 0; i < 208; i++) { if (i < value.length()) key52[i] = value[i]; else key52[i] = 0; }insertIndex(index, key52, p); break;
                case 209: case 210: case 211: case 212: array<char, 212> key53; for (unsigned int i = 0; i < 212; i++) { if (i < value.length()) key53[i] = value[i]; else key53[i] = 0; }insertIndex(index, key53, p); break;
                case 213: case 214: case 215: case 216: array<char, 216> key54; for (unsigned int i = 0; i < 216; i++) { if (i < value.length()) key54[i] = value[i]; else key54[i] = 0; }insertIndex(index, key54, p); break;
                case 217: case 218: case 219: case 220: array<char, 220> key55; for (unsigned int i = 0; i < 220; i++) { if (i < value.length()) key55[i] = value[i]; else key55[i] = 0; }insertIndex(index, key55, p); break;
                case 221: case 222: case 223: case 224: array<char, 224> key56; for (unsigned int i = 0; i < 224; i++) { if (i < value.length()) key56[i] = value[i]; else key56[i] = 0; }insertIndex(index, key56, p); break;
                case 225: case 226: case 227: case 228: array<char, 228> key57; for (unsigned int i = 0; i < 228; i++) { if (i < value.length()) key57[i] = value[i]; else key57[i] = 0; }insertIndex(index, key57, p); break;
                case 229: case 230: case 231: case 232: array<char, 232> key58; for (unsigned int i = 0; i < 232; i++) { if (i < value.length()) key58[i] = value[i]; else key58[i] = 0; }insertIndex(index, key58, p); break;
                case 233: case 234: case 235: case 236: array<char, 236> key59; for (unsigned int i = 0; i < 236; i++) { if (i < value.length()) key59[i] = value[i]; else key59[i] = 0; }insertIndex(index, key59, p); break;
                case 237: case 238: case 239: case 240: array<char, 240> key60; for (unsigned int i = 0; i < 240; i++) { if (i < value.length()) key60[i] = value[i]; else key60[i] = 0; }insertIndex(index, key60, p); break;
                case 241: case 242: case 243: case 244: array<char, 244> key61; for (unsigned int i = 0; i < 244; i++) { if (i < value.length()) key61[i] = value[i]; else key61[i] = 0; }insertIndex(index, key61, p); break;
                case 245: case 246: case 247: case 248: array<char, 248> key62; for (unsigned int i = 0; i < 248; i++) { if (i < value.length()) key62[i] = value[i]; else key62[i] = 0; }insertIndex(index, key62, p); break;
                case 249: case 250: case 251: case 252: array<char, 252> key63; for (unsigned int i = 0; i < 252; i++) { if (i < value.length()) key63[i] = value[i]; else key63[i] = 0; }insertIndex(index, key63, p); break;
                case 253: case 254: case 255: case 256:default: array<char, 256> key64; for (unsigned int i = 0; i < 256; i++) { if (i < value.length()) key64[i] = value[i]; else key64[i] = 0; }insertIndex(index, key64, p); break;
                }
            }
        } catch (...) {
            cerr << "insertIndex failed\n";
            return false;
        }
        return true;
    }

    Pointer rtop(const RecordPointer& p) {
        return Pointer{ p.getBlockNo() , p.getBlockOffset() };
    }
    bool writePosition(const string& name, const void* cont, const Pointer& p, size_t size) {
        try {
            memmove(getPosition(name, p), cont, size);
            BufferManager::getBlock(name, "index", p.blockNo).setDirty();
        } catch (...) {
            cerr << "writePosition failed\n";
            return false;
        }
        return true;
    }
    void* getPosition(const string& name, const Pointer& p) {
        BufferManager::getBlock(name, "index", p.blockNo).pinBlock();
        char* pagePointer = BufferManager::getBlock(name, "index", p.blockNo).getBlockContent();
        return  (pagePointer + p.blockOffset);
    }
    void endOccupation(const string& name, const Pointer& p) {
        BufferManager::getBlock(name, "index", p.blockNo).unpinBlock();
    }
    Tail* getTail(const string& name, const Pointer& p) {
        return (Tail*)getPosition(name, p);
    }

}