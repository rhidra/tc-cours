/**
 * compress.c
 *
 * Compress a file given a parameter using the Huffman compression algorithm.
 * Usage: ./mp3_20180326 -{c|d} <file>
 *
 *  -c : Compress the file. Add the .zz extension to a compressed file.
 *
 *  -d : Decompress a file previously compressed using the -c option.
 *       Does not work on a file not compressed using this program.
 *
 * Author : Rémy Hidra
 *
 * 2018/2019
 */

#include "compress.h"

int main(int argc, char **argv) {
    // Arguments parsing
    if (argc != 3) {
        printf("Usage: ./mp3_20180326 -{c|d} <file>\n");
        exit(1);
    }

    int is_compressing;
    if (!strcmp(argv[1], "-c")) {
        is_compressing = 1;
    } else if (!strcmp(argv[1], "-d")) {
        is_compressing = 0;
    } else {
        printf("Usage: ./mp3_20180326 -{c|d} <file>\n");
        exit(1);
    }

    // File opening
    FILE *file = fopen(argv[2], "r");
    if (file == NULL) {
        printf("File does not exist !\n");
        exit(1);
    }

    // File loading
    char *data;
    OUTPUT output;
    int size;

    // Get the input file size
    fseek(file, 0L, SEEK_END);
    size = ftell(file);
    fseek(file, 0L, SEEK_SET);
    data = malloc(sizeof(char) * size);
    if (data == NULL) {
        printf("Can't allocate memory !\n");
        exit(1);
    }

    // Read the file
    if (fread(data, sizeof(char), size, file) != size) {
        printf("Can't read file !\n");
        exit(1);
    }

    // Compression / Decompression
    if (is_compressing) {
        printf("Original size : \t%d bytes\n", size);
        output = compress(data, size);
        printf("Compressed size : \t%d bytes\n", output.size);
    } else {
        printf("Compressed size : \t%d bytes\n", size);
        output = decompress(data, size);
        printf("Uncompressed size : \t%d bytes\n", output.size);
    }

    fclose(file);

    // Write the output file
    write_file(argv[2], output.data, output.size, is_compressing);

    // Free memory allocation
    free(data);
    free(output.data);

    return 0;
}

/**
 * build_huffman_tree()
 * Build the Huffman compression tree using a table of each symbol with their frequency
 * of appearance in the input file.
 */
NODE* build_huffman_tree(char **data, int freq[], int size) {
    // Initializing the heap
    HEAP *heap = init_heap(data, freq, size);
    NODE *left, *right, *new;

    while (heap->size > 1) {
        // Extract the 2 minimum nodes of the heap
        left = extract(heap);
        right = extract(heap);

        // Fusion the two nodes under a parent with a frequency sum of the other two
        new = new_node("\0", left->freq + right->freq);
        new->left = left;
        new->right = right;

        // Insert the new node in the heap
        insert(heap, new);
    }

    // When only one node is remaining in the heap
    // It is the root of the Huffman tree
    NODE *tree = extract(heap);
    free(heap);
    return tree;
}

/**
 * compress()
 * Main function used to compress some raw data.
 */
OUTPUT compress(char data[], int size) {
    int i, k, j, size_symbols = 0, is_found, unencoded_bits;

    // if BYTES_PER_SYMBOL = 2
    // symbols = {"aa", "ab", "bb", ..., "zz"}
    char **symbols = (char**) malloc(sizeof(char*) * QUANTITY_OF_SYMBOLS);
    for (i = 0; i < QUANTITY_OF_SYMBOLS; i++)
        symbols[i] = (char*) malloc(sizeof(char) * BYTES_PER_SYMBOL);
    int freq[QUANTITY_OF_SYMBOLS];
    char buf[BYTES_PER_SYMBOL];

    // Building Symbols <-> Frequency table
    for (i = 0; i < size; i += BYTES_PER_SYMBOL) {
        memcpy(buf, &data[i], BYTES_PER_SYMBOL);
        is_found = 0;
        for (j = 0; j < size_symbols; j++) {
            if (!memcmp(symbols[j], buf, BYTES_PER_SYMBOL)) {
                // Symbol already exist in the table
                freq[j]++;
                is_found = 1;
                break;
            }
        }

        if (!is_found) {
            // Add the new symbol to the table
            size_symbols++;
            freq[size_symbols - 1] = 1;
            memcpy(symbols[size_symbols - 1], buf, BYTES_PER_SYMBOL);
        }
    }

    // Building the Huffman tree
    NODE *tree = build_huffman_tree(symbols, freq, size_symbols);
    int tree_height = height_tree(tree);

    // Building the table symbols <=> code
    char **symbols_code = (char**) malloc(sizeof(char*) * size_symbols);
    for (i = 0; i < size_symbols; i++) {
        symbols_code[i] = (char*) malloc(sizeof(char) * tree_height);
        if (!symbols_code[i]) {
            printf("Can't allocate memory !\n");
            exit(1);
        }
    }
    build_codes(tree, symbols, symbols_code, size_symbols);

    // Compression
    int *compressed_data_bits = (int*) malloc(sizeof(int) * tree_height * size / BYTES_PER_SYMBOL);
    memset(compressed_data_bits, '\0', tree_height * size / BYTES_PER_SYMBOL);
    int size_compression = compress_data(data, size, symbols, symbols_code, size_symbols, compressed_data_bits);

    // If some bits are going to be left unencoded
    // They are left raw in the compressed file
    unencoded_bits = size_compression % CHAR_BIT;

    // Building the header of the compressed file
    char header[SIZE_BUFFER_HEADER];
    memset(header, '\0', SIZE_BUFFER_HEADER);
    sprintf(header, "%d|%d|", size_symbols, unencoded_bits);
    int header_size = strlen(header);
    for (i = 0; i < size_symbols; i++) {
        for (k = 0; k < BYTES_PER_SYMBOL; k++) {
            header[header_size+k] = symbols[i][k];
        }
        header_size += k;
        header_size += sprintf(header+header_size, "%d|", freq[i]);
    }

    // Convert bits in bytes
    char *data_compressed = (char*) malloc(size_compression / CHAR_BIT + sizeof(char) * SIZE_BUFFER_HEADER);
    memset(data_compressed, '\0', size_compression / CHAR_BIT + sizeof(char) * SIZE_BUFFER_HEADER);
    memcpy(data_compressed, header, header_size);
    bits2bytes(data_compressed + header_size, compressed_data_bits, size_compression);

    // Writing the output
    OUTPUT output;
    output.data = data_compressed;
    output.size = size_compression / CHAR_BIT + header_size + unencoded_bits;

    // Free memory
    for (i = 0; i < size_symbols; i++)
        free(symbols_code[i]);
    for (i = 0; i < QUANTITY_OF_SYMBOLS; i++)
        free(symbols[i]);
    free(symbols);
    free(symbols_code);
    free(compressed_data_bits);
    free_tree(tree);

    return output;
}

/**
 * build_codes()
 * Go through the Huffman tree to build a table of the symbols code.
 */
void build_codes(NODE *tree, char **symbols, char **symbols_code, int size_symbols) {
    int i, tree_height = height_tree(tree);
    char *bits = (char*) malloc(sizeof(char) * tree_height);

    for (i = 0; i < size_symbols; i++) {
        memset(bits, '\0', tree_height);
        get_code(tree, symbols[i], bits, 0);
        memcpy(symbols_code[i], bits, tree_height);
    }

    free(bits);
}

/**
 * get_code()
 * Search the right combination of bit to code a given symbol using the Huffman tree.
 */
int get_code(NODE *tree, char symbol[BYTES_PER_SYMBOL], char *bits, int n) {
    int finished = 0;
    if (tree->left) {
        bits[n] = '0';
        finished = get_code(tree->left, symbol, bits, n+1);
    }

    if (!finished && tree->right) {
        bits[n] = '1';
        finished = get_code(tree->right, symbol, bits, n+1);
    }

    if (!finished && !tree->left && !tree->right && !memcmp(symbol, tree->symbol, BYTES_PER_SYMBOL))
        return 1;
    if (!finished)
        bits[n] = '\0';
    return finished;
}

/**
 * compress_data()
 * Build an array of bits to code the raw data, using the symbols code table.
 */
int compress_data(char data[], int size, char **symbols, char **symbols_code, int size_symbols, int *compressed_data_bits) {
    int i, j, k, size_compression = 0;

    for (i = 0; i < size; i+=BYTES_PER_SYMBOL) {
        for (j = 0; j < size_symbols; j++) {
            if (!memcmp(&data[i], symbols[j], BYTES_PER_SYMBOL)) {
                // Write the matching compressed block
                k = 0;
                while (symbols_code[j][k] != '\0') {
                    compressed_data_bits[size_compression++] = (symbols_code[j][k++] == '1') ? 1 : 0;
                }
            }
        }
    }

    return size_compression;
}

/**
 * bits2bytes()
 * Convert the array of bits in an array of bytes.
 */
void bits2bytes(char data_compressed[], int compressed_data_bits[], int size_compression) {
    int i, j;

    for (i = 0; i <= size_compression-CHAR_BIT; i += CHAR_BIT) {
        data_compressed[i/CHAR_BIT] = 0x00;
        for (j = 0; j < CHAR_BIT; j++) {
            if (compressed_data_bits[i+j]) {
                data_compressed[i/CHAR_BIT] |= (1 << j);
            }
        }
    }

    // If bits are left unencoded yet
    // They are written as raw numbers in the file
    if (size_compression % CHAR_BIT != 0) {
        for (j = 0; j+i < size_compression; j++) {
            if (compressed_data_bits[i+j]) {
                data_compressed[i/CHAR_BIT+j] = '1';
            } else {
                data_compressed[i/CHAR_BIT+j] = '0';
            }
        }
    }
}

/**
 * decompress()
 * Main function used for decompressing files.
 * Use the header to get the frequencies of each character.
 * Then, it builds the same Huffman tree used for compression and
 * decompress the data.
 */
OUTPUT decompress(char data[], int size) {
    int i;

    // Parsing the header
    HEADER header = parse_header(data, size);

    // Building the Huffman tree
    NODE *tree = build_huffman_tree(header.symbols, header.freq, header.size_symbols);
    int tree_height = height_tree(tree);

    // Building the table symbols <=> code
    char **symbols_code = (char**) malloc(sizeof(char*) * header.size_symbols);
    for (i = 0; i < header.size_symbols; i++) {
        symbols_code[i] = (char*) malloc(sizeof(char) * tree_height);
        if (!symbols_code[i]) {
            printf("Can't allocate memory !\n");
            exit(1);
        }
    }
    build_codes(tree, header.symbols, symbols_code, header.size_symbols);

    // Convert bytes to integer bits array
    int *compressed_data_bits = (int*) malloc(sizeof(int) * CHAR_BIT * (size - header.size_header));
    bytes2bits(data + header.size_header, compressed_data_bits, size - header.size_header, header.unencoded_bits);

    // Decompress bits array
    OUTPUT output;
    char *data_uncompressed = (char*) malloc(sizeof(char) * CHAR_BIT * (size - header.size_header));
    output.size = decompress_data(compressed_data_bits, CHAR_BIT * (size - header.size_header - header.unencoded_bits) + header.unencoded_bits, header.symbols, symbols_code, header.size_symbols, data_uncompressed, tree_height);
    output.data = data_uncompressed;

    // Free memory
    for (i = 0; i < header.size_symbols; i++)
        free(header.symbols[i]);
    for (i = 0; i < header.size_symbols; i++)
        free(symbols_code[i]);
    free(symbols_code);
    free(header.symbols);
    free(header.freq);

    return output;
}

/**
 * decompress_data()
 * Using the symbols code table, decompress the array of bits to extract each symbols.
 */
int decompress_data(int *compressed_data_bits, int size_compressed_bits, char **symbols, char **symbols_code, int size_symbols, char *data_uncompressed, int tree_height) {
    char *buf = (char*) malloc(sizeof(char) * (tree_height+1));
    int i, j, k, ibuf = 0, idata = 0;
    memset(buf, '\0', tree_height+1);

    for (i = 0; i < size_compressed_bits; i++) {
        buf[ibuf++] = '0' + compressed_data_bits[i];
        for (j = 0; j < size_symbols; j++) {
            if (!strcmp(buf, symbols_code[j])) {
                for (k = 0; k < BYTES_PER_SYMBOL; k++) {
                    data_uncompressed[idata + k] = symbols[j][k];
                }
                idata += BYTES_PER_SYMBOL;
                ibuf = 0;
                memset(buf, '\0', tree_height+1);
                break;
            }
        }
    }

    free(buf);

    return idata;
}

/**
 * parse_header()
 * Parse the header of the file. The format of the header must be :
 * <quantity of symbols>|<quantity of unencoded bits>|<symbol 1><symbol 1's frequency>| ...
 */
HEADER parse_header(char data[], int size) {
    char buf[SIZE_BUFFER];
    int i = 0, j, k;
    HEADER header;

    // Quantity of different symbols
    j = 0;
    memset(buf, '\0', SIZE_BUFFER);
    while (data[i] != '|')
        buf[j++] = data[i++];
    header.size_symbols = (int) strtol(buf, NULL, 10);
    header.symbols = (char**) malloc(sizeof(char*) * header.size_symbols);
    header.freq = (int*) malloc(sizeof(int) * header.size_symbols);

    // Quantity of unencoded bits
    j = 0;
    ++i;
    memset(buf, '\0', SIZE_BUFFER);
    while (data[i] != '|')
        buf[j++] = data[i++];
    header.unencoded_bits = (int) strtol(buf, NULL, 10);

    // Symbols and their frequency
    // Ex format: aa568|bb123|cc456|
    ++i;
    for (j = 0; j < header.size_symbols; j++) {
        header.symbols[j] = (char*) malloc(sizeof(char) * BYTES_PER_SYMBOL);
        for (k = 0; k < BYTES_PER_SYMBOL; k++) {
            header.symbols[j][k] = data[i++];
        }

        k = 0;
        memset(buf, '\0', SIZE_BUFFER);
        while (data[i] != '|') {
            buf[k++] = data[i++];
        }
        ++i;
        header.freq[j] = (int) strtol(buf, NULL, 10);
    }

    header.size_header = i;

    return header;
}

/**
 * bytes2bits()
 * Convert the array of raw bytes in a array of bits.
 */
void bytes2bits(char data_compressed[], int compressed_data_bits[], int size_compression, int unencoded_bits) {
    int i,j;

    for (i = 0; i < size_compression - unencoded_bits; i++) {
        for (j = 0; j < CHAR_BIT; j++) {
            compressed_data_bits[i * CHAR_BIT + (CHAR_BIT - j - 1)] = (int) !!((data_compressed[i] << j) & 0x80);
        }
    }

    // Unencoded bits
    for (; i < size_compression; i++) {
        compressed_data_bits[(size_compression - unencoded_bits) * CHAR_BIT + i - (size_compression - unencoded_bits)] = data_compressed[i] - '0';
    }
}

/**
 * write_file()
 *
 * Write the data in an output file named correctly.
 */
void write_file(char *name, char *data, int size, int is_compressing) {
    char output_name[100];
    int i;
    for (i = 0; i < 100; i++) {
        output_name[i] = '\0';
    }
    if (is_compressing)
        sprintf(output_name, "%s.zz", name);
    else
        sprintf(output_name, "%s.yy", name);

    FILE *file = fopen(output_name, "w");
    if (file == NULL) {
        printf("Can't write file !\n");
        exit(1);
    }
    if (fwrite(data, sizeof(char), size, file) != size) {
        printf("Can't write file !\n");
        exit(1);
    }
}
