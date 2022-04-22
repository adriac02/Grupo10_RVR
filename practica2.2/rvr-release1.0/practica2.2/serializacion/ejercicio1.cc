#include "Serializable.h"

#include <iostream>
#include <string>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

class Jugador: public Serializable
{
public:
    Jugador(const char * _n, int16_t _x, int16_t _y):x(_x),y(_y)
    {
        strncpy(name, _n, 80);
    };

    virtual ~Jugador(){};

    void to_bin()
    {
        _size = sizeof(int16_t) * 2 + sizeof(char) * 80;

        alloc_data(_size);

        char* temporary = _data;

        memccpy(temporary, name, 80 * sizeof(char));

        temp += sizeof(char);

        memccpy(temp, &x, sizeof(int16_t));    
    }

    int from_bin(char * data)
    {
        char* aux = data;

        memccpy(name, temp, 80 * sizeof(char));

        aux += 80 * sizeof(char);

        memccpy(&x, aux, int16_t);


        return 0;
    }


public:
    char name[80];

    int16_t x;
    int16_t y;
};

int main(int argc, char **argv)
{
    Jugador one_r("", 0, 0);
    Jugador one_w("Player_ONE", 123, 987);

    // 1. Serializar el objeto one_w
    one_w.to_bin();
    // 2. Escribir la serialización en un fichero
    int fd = fopen(",/jugador.bin", O_CREAT | O_TRUNC | O_RDWR, 0666);
    fwrite(fd, one_w.data(), one_w.size());
    fclose(fd);
    // 3. Leer el fichero
    char buffer[256];
    fd = fopen(",/jugador.bin", O_RDONLY);

    fread(fd, buffer, 256);
    fclose(fd);
    // 4. "Deserializar" en one_r
    one_r.from_bin(buffer);
    // 5. Mostrar el contenido de one_r

    return 0;
}

