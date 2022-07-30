#include <iostream>		    // entradas salidas en consola y string cout cin ...
#include <fstream> 		    // manejo de archivos
#include <vector>           // gestiona las listas / arreglos / buffers
#include <string>
//#include <cstring>
#include <sstream> 
#include "../lib/global.h"
#include <limits>

using namespace std;
struct provincia
{
    char sNombre[50];
    int iPoblacion;
    float fTemperatura;
    char lstPlatoTipico[100];
    unsigned int id;
};
vector <provincia> lstProvincia;
const string pathfilebinary = "resorce/database/delivery.dat";


bool eliminarProvincia();
bool leerArchivoBinario();
unsigned int longitud_lista_provincias = 0;

void escribirArchivoBinario();

void presentarProvincias();      
void presentarProvincia();      
void presentarProvincia(provincia p);
void Buscarprovincia();
bool buscarAvanzado();
void agregarProvincia();   
void acercade();      

int menu();
string tolowerStr(string str);
void segmentarCadena( const string  str, const char delim,  vector <string> &lst ); 


int main()
{
    leerArchivoBinario();
    do{
        switch (menu())
        {
            case AGREGAR:
                agregarProvincia();
                break;
            case PRESENTAR:
                presentarProvincias();
                break;
            case GUARDAR_BINARIO:
                escribirArchivoBinario();
                break;
            case Buscar:
                Buscarprovincia();
                break;
            case BuscarAvanzado:
                buscarAvanzado();
                break;
            case ELIMINAR:
                eliminarProvincia();
                break;
            case ACERCADE:
                acercade();
                break;
            case SALIR:
                cout << "bye bye ...";
                exit(0);
            default:
                cout << "Seleccion no valida \n";
                break;
        }
    }while (true);
} 

void setColor(int Background, int Text){ 
    int colorTexto= Text + (Background * 16);         // los colores van del 0 al 255 por eso se multiplica por 16
    HANDLE terminal = GetStdHandle(STD_OUTPUT_HANDLE);   // referenciamos a la consola.
    SetConsoleTextAttribute(terminal, colorTexto); 
}

bool existRepetido(string elemento)
{
    bool ban=false;
    for (auto &&prov : lstProvincia)   
        if (tolowerStr(prov.sNombre)==tolowerStr(elemento))
        {
            cout << elemento << ", la provincia ya existe..! ";
            ban=true;
            continue;
        }
    return ban;
}


bool leerArchivoBinario()
{
    ifstream rf(pathfilebinary, ios::in | ios::binary);
    cout << "Abrir archivo:" << pathfilebinary << endl;
    if(!rf) 
    {
        cout << "error" << endl;
        return false;
    } 
    provincia tp[1];
    while(rf.read((char *) &tp[0], sizeof(provincia)))
    {
        lstProvincia.push_back(tp[0]);
    }
    longitud_lista_provincias = tp[0].id;
    rf.close();
    return true;
}

bool eliminarProvincia()
{
    int indexPet=0;
    string prov;
    string sn;
    bool encontrado = false;
    setColor(0,11);
    cout<<"-- << ELIMINAR PROVINCIA >> --"<< endl;
    cout<<"Ingrese el nombre de la provincia que desea eliminar: ";
    getline (cin,prov);    
    for (auto &&provincia : lstProvincia)  
    {         
        if (tolowerStr(provincia.sNombre)== tolowerStr(prov))
        {
            presentarProvincia(provincia);
            encontrado= true;
            setColor(0,14);
            cout << provincia.sNombre << provincia.id << endl;
            cout<<"Eliminar provincia? (s/n)";
            cin >>sn;
            if (sn=="s")
            {
                lstProvincia.erase(lstProvincia.begin()+indexPet);
                setColor(0,15);
                cout<<"Eliminado correctamente!!";
                return true;
            }
        }
        indexPet++;
    }
    if (!encontrado)
        cout<<"No se encontro la provincia "<<prov<<endl;
    return false;
}

void escribirArchivoBinario()
{
    ofstream f(pathfilebinary, ios::out | ios_base::binary );
    cout << endl << "Escribir archivo: " << pathfilebinary << endl;
    if(f.good())
    {
        for (auto &&prov : lstProvincia) 
            f.write((char *) &prov, sizeof(provincia));
        //f.write((char*)&lstProvincia[0], lstProvincia.size() * sizeof(provincia));
    }
    f.close();
}

void agregarProvincia()
{
    string str= "s";
    do
    {
        struct provincia prov;
        setColor(0,10);
        cout <<endl << "-- Ingresar datos de provincia  -- " << endl ;
        cout <<"<+> Nombre: ";
        cin.getline (prov.sNombre, 50, '\n');
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout <<"<+> Poblacion: ";
        cin >> prov.iPoblacion;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout <<"<+> Temperatura: ";
        cin >> prov.fTemperatura;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        setColor(0,4);
        cout <<"<+> PlatoTipico (separados por coma): ";
        cin.getline (prov.lstPlatoTipico, 100, '\n');
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (!existRepetido(prov.sNombre))
        {
            prov.id = longitud_lista_provincias + 1;
            longitud_lista_provincias++;
            lstProvincia.push_back(prov);
        }
        setColor(0,7);
        cout << "Deseas salir (s): " ;
        cin >> str;
        cin.clear();
    } while (str != "s");
}
void Buscarprovincia()
{
    setColor(0,9);
    cout << "------ Buscar Provincia -------" << endl;
    bool encondrado = false;
    string prov = "";
    cout <<"Ingresa el Nombre de la provincia: ";
    getline (cin, prov);

    for (auto &&provincia : lstProvincia)
    {
        if (tolowerStr(provincia.sNombre) == tolowerStr(prov))
        {
            presentarProvincia(provincia);
            encondrado = true;
        }
    }
    if (!encondrado) // if(ban == 0 )
    cout <<"No se encontro la provincia " << prov << endl; 
}

void acercade()
{
    setColor(0,9);
    cout << "\nIntegrantes:\n\n"
    << "paul.cajas@epn.edu.ec - Paul Cajas\n"
    << "pablo.hidalgo01@epn.edu.ec - Pablo Hidalgo\n" 
    << "rodrigo.haro@epn.edu.ec - Rodrigo Haro\n"
    << "alexis.chalacan@epn.edu.ec - Alexis Chalacan\n"
    << "mateo.carrillo@epn.edu.ec - Mateo Carrillo\n"
    << "joel.altamirano@epn.edu.ec - Joel Altamirano\n";
}

bool buscarAvanzado()
{
    char nombreProvincia [50];
    int longitud = 0;

    cout << "Nombre de provincia: ";
    fflush(stdin);
    fgets(nombreProvincia, 50, stdin);

    for (int i = 0; nombreProvincia[i] != '\0' && nombreProvincia[i] != '\n'; i++)
        longitud++;

    for (auto &provincia : lstProvincia)
    {
        int longitudlista = 0;
        float parecido = 0;

        for (int i = 0; provincia.sNombre[i] != '\0'; i++)
        {
            longitudlista++;
        }
        // entrada mas grande que la de la lista
        for (int iteradorpalabra = 0; longitud - iteradorpalabra >= longitudlista; iteradorpalabra++)
        {
            parecido = 0;
            for (int i = 0, a = iteradorpalabra; provincia.sNombre[i] != '\0'; i++, a++)
            {
                if (tolower(nombreProvincia[a]) == tolower(provincia.sNombre[i]))
                    parecido += (float) 1 / (float) longitudlista;
            }
            if (parecido >= 0.75)
            {
                setColor(0,15);
                cout << endl << "Dentro de su entrada se ha encontrado:\t";
                setColor(10,0);
                for (int b = iteradorpalabra, i = 0; i < longitudlista; b++, i++)
                    cout << nombreProvincia[b];
                setColor(0,9);
                cout << "\nQue coincide en un "<< parecido*100 << "% " << "con " << provincia.sNombre << endl;
                setColor(0,15);
                cout << "Presentando informacion de " << provincia.sNombre;
                setColor(0,9);
                cout << endl << "Poblacion:\t"<< provincia.iPoblacion 
                << endl << "Temperatura:\t" << provincia.fTemperatura
                << endl << "Platos tipicos:\t" << provincia.lstPlatoTipico << endl;
                setColor(0,15);
                return true;
            }
        }
        // entrada mas pequena que la de la lista
        if (longitud < longitudlista)
        {
            for (int i = 0; provincia.sNombre[i] != '\0' && nombreProvincia[i] != '\n'; i++)
            {
                if (tolower(nombreProvincia[i]) == tolower(provincia.sNombre[i]))
                    parecido += (float) 1 / (float) longitudlista;
            }
            if (parecido >= 0.75)
            {
                setColor(0,15);
                cout << endl << "Dentro de su entrada se ha encontrado:\t";
                setColor(10,0);
                for (int i = 0; i < longitud; i++)
                    cout << nombreProvincia[i];
                setColor(0,9);
                cout << "\nQue coincide en un "<< parecido*100 << "% " << "con " << provincia.sNombre << endl;
                setColor(0,15);
                cout << "Presentando informacion de " << provincia.sNombre;
                setColor(0,9);
                cout << endl << "Poblacion:\t"<< provincia.iPoblacion 
                << endl << "Temperatura:\t" << provincia.fTemperatura
                << endl << "Platos tipicos:\t" << provincia.lstPlatoTipico << endl;
                setColor(0,15);
                return true;
            }
        }
    }
    setColor(0,15);
    cout << "\nNo se encontraron coincidencias" << endl;
    return false;
}

void presentarProvincia(provincia p)
{
    setColor(0,9);
    cout<<"Id: "        << p.id <<endl;
    cout<<"Nombre: "        << p.sNombre<<endl;
    cout<<"Poblacion: "     << p.iPoblacion<<endl;
    cout<<"Temperatura: "   << p.fTemperatura<<endl;
    cout<<"Platos-Tipicos: "   << p.lstPlatoTipico<<endl <<endl;
}
void presentarProvincias(){
    cout<<endl<<"-------    Provincias   ----------"<<endl;
    for(auto &&prov : lstProvincia){
    presentarProvincia(prov);

    }
}


int menu()
{
    int eleccion;
    do
    {
        setColor(0,13);
        cout << endl
        << "()---Provincias del Ecuador---()\n"         << endl
        << "Ingresa una opcion: \n"                  << endl
        << AGREGAR          << " | Agregar provincias           |"  << endl
        << PRESENTAR        << " | listado de provincias        |"  << endl
        << GUARDAR_BINARIO  << " | Guardar provincias           |"  << endl
        << Buscar           << " | Buscar provincias            |"  << endl
        << BuscarAvanzado   << " | Buscar avanzado              |"  << endl
        << ELIMINAR         << " | Eliminar                     |"  << endl
        << ACERCADE         << " | Acerca de                    |"  << endl
        << SALIR            << " | Salir del sistema            |"  << endl
        << "\nSu seleccion:";
        cin >> eleccion;
        cin.clear();
        fflush(stdin);
    }while (eleccion < 0 || eleccion > 7); 
    return eleccion;
}
string tolowerStr(string str)  
{
    for (int x=0; x < str.length(); x++)
        str[x] = tolower(str[x]);
    return str;
}
void segmentarCadena( const string  str, const char delim,  vector<string> &outlst )  
{  
    string strDiv;  
    stringstream s(str);  
    while ( getline (s, strDiv, delim) )  
        outlst.push_back(strDiv);  
}

/* 

TAREA: deliberyBin
- 0.5 por item resuelto
- Equipos de 5 o 6 personas

    | Agregar provincias      |   << arreglar, evitar repetidos, Agregar a la estructura unsigned int Id (autoincremental)
    | Presentar provincias    |   << listar todas las provincias
    | Buscar provincia        |   << pedir nombre de provincia ... buscar y presentar : LOja 
    | Buscar Avanzada         |   << pedir nombre de provincia ... buscar y presentar las que coindidan : loxa, --> loja
    | Guardar provincias      |
    | Eliminar provincias     |
0| Salir del sistema      |

>> captuas de pantalla del trabajo colaborativo
<< investigar como recupera directamente del archivo la estructura de datos >>
>> agregar color 0,1

*/

/* Funciones para recuperar una estructura de un archivo.
Tenemos presentes las siguientes funciones.

file.seekg = Está nos ayuda a buscar una posición aleatoria de un archivo, ayudandonos a establecer 
la posición de un caracter que sera extraido del flujo de entrada de un archivo.
        fichero.seekg(10, ios::cur)
        fichero.seekg(0, ios::beg);
        fichero.seekg(0, ios::end);

file.tellg = Devuelve la posición de un caracter actual en el flujo de entrada, si el puntero no 
encuentra la posición devuelve un -1

Con estas y lógicamente el correcto uso de otras funciones. Se puede procesar la extracción de una estructura de datos de un archivo.

*/
