#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <wchar.h>

typedef struct __attribute__((packed)) header
{
    short un;
    int deux;
    short trois;
    short quatre;
    int cinq;
    int six;
    int sept;
    int huit;
    short neuf;
    short dix;
    int onze;
    int douze;
    int treize;
    int quator;
    int seize;
    int dix_sept;
}               header_t;

typedef union color
{
    unsigned char couleur[4];
    unsigned int  couleur_int;
}           color_t;

int main(int ac, char **av)
{
  if (ac != 2)
    return (0);

    color_t tmp;
    header_t head;
    int i = 0;
    int fd = open(av[1], O_RDONLY);
    read(fd, &head, 54);
    char* toto = malloc((head.cinq - 54) * sizeof(char));
    if (toto == NULL)
    {
        printf("MALLOC FAIL\n");
        return;
    }
    read(fd, toto, (head.cinq - 54));
    int *tab = malloc((head.sept * head.huit) * sizeof(int));
    if (tab == NULL)
    {
        printf("MALLOC FAIL\n");
        return;
    }
    printf("%d  %d  %d  \n", head.cinq, head.sept, head.dix);
    read(fd, tab, (head.sept * head.huit) * 4);
    close(fd);
    int loop = 1;
            int j = head.huit;
            write(1, "\e[1;1H\e[2J", 12);
            while (j > 0)
            {
                i = 0;
                while (i < head.sept)
                {
                    tmp.couleur_int = tab[j * head.sept + i];
                    int titi;
                    //int titi = tmp.couleur_int / (4294967295 / loop);
                    if (tmp.couleur[2] < 127 && tmp.couleur[1] < 127 && tmp.couleur[0] < 127)
                        titi = 0;
                    else if (tmp.couleur[2] > 127 && tmp.couleur[1] < 127 && tmp.couleur[0] < 127)
                        titi = 1;
                    else if (tmp.couleur[2] < 127 && tmp.couleur[1] > 127 && tmp.couleur[0] < 127)
                        titi = 2;
                    else if (tmp.couleur[2] > 127 && tmp.couleur[1] > 127 && tmp.couleur[0] < 127)
                        titi = 3;
                    else if (tmp.couleur[2] < 127 && tmp.couleur[1] < 127 && tmp.couleur[0] > 127)
                        titi = 4;
                    else if (tmp.couleur[2] > 127 && tmp.couleur[1] < 127 && tmp.couleur[0] > 127)
                        titi = 5;
                    else if (tmp.couleur[2] < 127 && tmp.couleur[1] > 127 && tmp.couleur[0] > 127)
                        titi = 6;
                    else if (tmp.couleur[2] > 127 && tmp.couleur[1] > 127 && tmp.couleur[0] > 127)
                        titi = 7;
                    else
                        titi = 7;
                    printf("\e[4%dm \e[0m", titi);
                    i++;
                }
                printf("\n");
                j--;
            }

}
