#include <iostream>
struct Alarma {
    void encenderAlarma() {
        std::cout << "Alarma encendida \n";
    }
    void apagarAlarma() {
        std::cout << "Alarma apagada \n";
    }
};

struct Agua {
    void cerrarGrifos() {
        std::cout << "Grifos cerrados \n";
    }
};

struct Electricidad {
    void apagarLuz() {
        std::cout << "Luces apagadas \n";
    }
    void encenderLuz() {
        std::cout << "Luces encendidas \n";
    }
};

struct FacadeCasa {

    void salirdeCasa() {
        alarma.encenderAlarma();
        agua.cerrarGrifos();
        elec.apagarLuz();
    }

    void volverCasa() {
        alarma.apagarAlarma();
        elec.encenderLuz();
    }

private:
    Alarma alarma;
    Agua agua;
    Electricidad elec;
};

int main() {
    FacadeCasa micasa;
    std::cout << "Salir de casa: \n";
    micasa.salirdeCasa();

    std::cout << "\n \n";

    std::cout << "Volver a casa: \n";
    micasa.volverCasa();

    return 0;
}

