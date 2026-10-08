// GOW-Port: espera procedural para recuperar un llamador propio desde una DLL de Windows.
#include <windows.h>
volatile unsigned ticks = 0;
__declspec(noinline) void EsperaPerfilProcedural()
{
    Sleep(10);
    ticks = ticks + 1; // Conservar el marco; evitar convertir Sleep en un salto final.
}
int main()
{
    for (unsigned i=0;i<1500;++i) EsperaPerfilProcedural();
    return 0;
}
