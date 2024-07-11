#include <iostream>
#include <vector>
using namespace std;

void print_rueda(vector<vector<int>> rueda) {
    int fechas_rueda = rueda[0].size();
    for (int i = 0; i < rueda.size(); i++) {
        for (int j = 0; j < fechas_rueda; j++) {
            if (rueda[i][j] >0){
                std::cout << " " << rueda[i][j] << "  ";
            }
            else{
                std::cout << rueda[i][j] << "  ";
            }
        }
        std::cout << '\n';
    }
}

void print_calendarizacion(vector<vector<int>>rueda1, vector<vector<int>> rueda2) {
    int fechas_rueda = rueda1[0].size();
    int rueda_actual = 1;
    for (int i = 0; i < rueda1.size(); i++) {

        for (int j = 0; j < fechas_rueda ; j++) {
            if (rueda1[i][j] >0){
                std::cout << " " << rueda1[i][j] << "  ";
            }
            else{
                std::cout << rueda1[i][j] << "  ";
            }
        }
        for (int j = 0; j < fechas_rueda; j++) {
            if (rueda2[i][j] >0){
                std::cout << " " << rueda2[i][j] << "  ";
            }
            else{
                std::cout << rueda2[i][j] << "  ";
            }
        }
        std::cout << '\n';
    }
}

vector<vector<int>> generacion_rueda_mirrored(vector<vector<int>> primera_rueda) {
    vector<vector<int>> segunda_rueda = primera_rueda;
    int cantidad_equipos = primera_rueda.size();
    int cantidad_fechas = primera_rueda[0].size();
    for (int i = 0; i < cantidad_equipos; i++) {
        for (int j = 0; j < cantidad_fechas; j++) {
            segunda_rueda[i][j] = -primera_rueda[i][j];
        }
    }
    return segunda_rueda;
}

vector<vector<int>> creacion_fixture_inicial(int cantidad_de_equipos) {

    vector<vector<int>> rueda_inical;

    //llenando rueda_inicial con 0, va a ser un vector de cantidad de equipo x cantidad de equipos - 1

    for (int i = 0; i < cantidad_de_equipos; i++)
    {
        vector<int> fila = {};
        for (int j = 0; j < cantidad_de_equipos - 1; j++)
        {
            fila.push_back(0);
        }
        rueda_inical.push_back(fila);
    }

    //creacion de vector inicial
    vector<int> vector_inical = {};

    vector_inical.push_back(cantidad_de_equipos);

    for (int i = 1; i < cantidad_de_equipos; i++) {
        vector_inical.push_back(i);
    }

    int ronda_actual = 1;

    while (ronda_actual < cantidad_de_equipos){
        //equipos en las posiciones 0 y 1 se enfrentan

        if (ronda_actual == 1){
            rueda_inical[cantidad_de_equipos-1][0] = vector_inical[1];
            rueda_inical[vector_inical[1]-1][0] = -vector_inical[0];
        }
        else if(ronda_actual==2 || ronda_actual==3){
            rueda_inical[cantidad_de_equipos-1][ronda_actual-1] = -vector_inical[1];
            rueda_inical[vector_inical[1]-1][ronda_actual-1] = vector_inical[0];
        }
        else if (ronda_actual%2 ==0){ //es par
            rueda_inical[cantidad_de_equipos-1][ronda_actual-1] = vector_inical[1];
            rueda_inical[vector_inical[1]-1][ronda_actual-1] = -vector_inical[0];
        }
        else{
            rueda_inical[cantidad_de_equipos-1][ronda_actual-1] = -vector_inical[1];
            rueda_inical[vector_inical[1]-1][ronda_actual-1] = vector_inical[0];
        }

        for(int i=2; i <= cantidad_de_equipos/2; i++){
            //el equipo en la posicion i se enfrenta al que esta en n+1-i

            if (i%2==0){
                rueda_inical[vector_inical[i]-1][ronda_actual-1] = vector_inical[cantidad_de_equipos+1-i];
                rueda_inical[vector_inical[cantidad_de_equipos+1-i]-1][ronda_actual-1] = -vector_inical[i];
            }
            else{
                rueda_inical[vector_inical[i]-1][ronda_actual-1] = -vector_inical[cantidad_de_equipos+1-i];
                rueda_inical[vector_inical[cantidad_de_equipos+1-i]-1][ronda_actual-1] = vector_inical[i];
            }
        }

        //Luego se realizan las rotaciones en el vector inicial

        for(int i =1; i<cantidad_de_equipos; i++){
            vector_inical[i] = vector_inical[i]-1;
            if (vector_inical[i] == 0){
                vector_inical[i] = cantidad_de_equipos-1;
            }
        }

        ronda_actual++;
    }

    return rueda_inical;
}

//primera version reparando localias ruedas SIMPLE
//recibe rueda 1 y 2, modifica las localias de la rueda 2 dos segun las de la rueda 1
vector<vector<int>> reparacion_rueda(vector<vector<int>> rueda1, vector<vector<int>> rueda2) {
    vector<vector<int>> rueda2_reparada = rueda2;
    int cantidad_equipos = rueda1.size();
    int cantidad_fechas = rueda1[0].size();

    for (int i = 0; i < cantidad_equipos; i++) {
        for (int j = 0; j < cantidad_fechas; j++) {
            for (int k = 0; k < cantidad_fechas; k++) {
                int rival_equipo_rueda1 = abs(rueda1[i][j]);
                int rival_equipo_rueda2 = abs(rueda2[i][k]);
                if (rival_equipo_rueda1 == rival_equipo_rueda2) {
                    if ((rueda1[i][j] > 0 && rueda2[i][k] > 0) || (rueda1[i][j] < 0 && rueda2[i][k] < 0)) {
                        rueda2_reparada[i][k] = -1* rueda2[i][k];
                        rueda2_reparada[rival_equipo_rueda1-1][k] = -1* rueda2[rival_equipo_rueda1-1][k];
                        
                        //para no seguir buscando el mismo enfrentamiento
                        k = cantidad_fechas;
                    }
                }
            }
        }
    }
    return rueda2_reparada;
}

vector<vector<vector<int>>> reparacion_ambas_ruedas(vector<vector<int>> rueda1, vector<vector<int>> rueda2){
    vector<vector<vector<int>>> ruedas_reparadas;
    vector<vector<int>> rueda1_actual = rueda1;
    vector<vector<int>> rueda2_actual = rueda2;
    int cantidad_equipos = rueda1.size();
    int cantidad_fechas = rueda1[0].size();

    for (int i = 0; i < cantidad_equipos; i++) {
        //cout << "Revisando equipo " << i+1 << '\n';
        for (int fecha_r1 = 0; fecha_r1 < cantidad_fechas; fecha_r1++) {
            for (int fecha_r2 = 0; fecha_r2 < cantidad_fechas; fecha_r2++) {
                //cout << "Revisando fecha " << fecha_r1+1 << " y " << fecha_r2+1 << '\n';
                bool conflicto_rueda1 = false;
                bool conflicto_rueda2 = false;
                if (abs(rueda1_actual[i][fecha_r1]) == abs(rueda2_actual[i][fecha_r2])) {
                    if ((rueda1_actual[i][fecha_r1] > 0 && rueda2_actual[i][fecha_r2] > 0) || (rueda1_actual[i][fecha_r1] < 0 && rueda2_actual[i][fecha_r2] < 0)) { 
                        // Hay conflicto, se debe revisar en cual de las dos ruedas se cambia la localia
                        //cout << "Conflicto en la fecha " << fecha_r1+1 << " y " << fecha_r2+1 << " con el equipo " << abs(rueda1_actual[i][fecha_r1]) << '\n';

                        if (fecha_r1 == 0 || fecha_r1 == 1){ //conflicto en la fecha 1 o 2
                            if (rueda1_actual[i][0] > 0 && rueda1_actual[i][1] > 0 || rueda1_actual[i][0] < 0 && rueda1_actual[i][1] < 0){ 
                                // se modifica la rueda 1 en caso que la localia de la fecha 1 sea igual a la de la fecha 2
                                rueda1_actual[i][fecha_r1] = -1* rueda1[i][fecha_r1];
                            }
                            else{
                                // se modifica la rueda 2
                                rueda2_actual[i][fecha_r2] = -1* rueda2[i][fecha_r2];
                            }
                        }
                        else if (fecha_r2 == cantidad_fechas-2 || fecha_r2 == cantidad_fechas-1){ // confico en las ultimas dos fechas (de la segunda rueda logicamente)
                            if (rueda2_actual[i][cantidad_fechas-2] > 0 && rueda2_actual[i][cantidad_fechas-1] > 0 || rueda2_actual[i][cantidad_fechas-2] < 0 && rueda2_actual[i][cantidad_fechas-1] < 0){
                                // se modifica la rueda 2 en caso que la localia de la fecha 18 (37) sea igual a la de la fecha 19 (38)
                                rueda2_actual[i][fecha_r2] = -1* rueda2[i][fecha_r2];
                            }
                            else{
                                // se modifica la rueda 1
                                rueda1_actual[i][fecha_r1] = -1* rueda1[i][fecha_r1];
                            }
                        }
                        else if (fecha_r1 == cantidad_fechas-1){ // ultima fecha primera rueda
                            if(rueda1_actual[i][cantidad_fechas-2] > 0 && rueda1_actual[i][cantidad_fechas-1] > 0 && rueda2_actual[i][0] > 0 || rueda1_actual[i][cantidad_fechas-2] < 0 && rueda1_actual[i][cantidad_fechas-1] < 0 && rueda2_actual[i][0] < 0){
                                rueda1_actual[i][fecha_r1] = -1* rueda1[i][fecha_r1];
                            }
                            else{
                                rueda2_actual[i][fecha_r2] = -1* rueda2[i][fecha_r2];
                            }
                        }
                        else if (fecha_r2 == 0){ // primera fecha segunda rueda
                            if(rueda1_actual[i][18] > 0 && rueda2_actual[i][0] > 0 && rueda2_actual[i][1] > 0 || rueda1_actual[i][18] < 0 && rueda2_actual[i][0] < 0 && rueda2_actual[i][1] < 0){
                                rueda2_actual[i][fecha_r2] = -1* rueda2[i][fecha_r2];
                            }
                            else{
                                rueda1_actual[i][fecha_r1] = -1* rueda1[i][fecha_r1];
                            }
                        }
                        else{ // es una fecha "normal"
                            // se revisa si las dos fechas adyacentes tienen la misma localia que la fecha actual
                            if (rueda1_actual[i][fecha_r1-1] > 0 && rueda1_actual[i][fecha_r1] > 0 && rueda1_actual[i][fecha_r1+1] > 0 || rueda1_actual[i][fecha_r1-1] < 0 && rueda1_actual[i][fecha_r1] < 0 && rueda1_actual[i][fecha_r1+1] < 0){
                                conflicto_rueda1 = true;
                            }
                            if (rueda2_actual[i][fecha_r2-1] > 0 && rueda2_actual[i][fecha_r2] > 0 && rueda2_actual[i][fecha_r2+1] > 0 || rueda2_actual[i][fecha_r2-1] < 0 && rueda2_actual[i][fecha_r2] < 0 && rueda2_actual[i][fecha_r2+1] < 0){
                                conflicto_rueda2 = true;
                            }
                            
                            if(conflicto_rueda1 == true && conflicto_rueda2 == false){ // solo la rueda 1 tiene conflicto
                                rueda1_actual[i][fecha_r1] = -1* rueda1[i][fecha_r1];
                            }
                            else if(conflicto_rueda1 == false && conflicto_rueda2 == true){ // solo la rueda 2 tiene conflicto
                                rueda2_actual[i][fecha_r2] = -1* rueda2[i][fecha_r2];
                            }
                            else{ // se elige la rueda a modificar de forma random
                                if (rand()%2 == 0){
                                    rueda1_actual[i][fecha_r1] = -1* rueda1_actual[i][fecha_r1];
                                }
                                else{
                                    rueda2_actual[i][fecha_r2] = -1* rueda2_actual[i][fecha_r2];
                                }
                            }
                        }
                        // Para no seguir buscando el mismo enfrentamiento
                        fecha_r2 = cantidad_fechas;
                    }
                }
            }
        }
    }
    ruedas_reparadas.push_back(rueda1_actual);
    ruedas_reparadas.push_back(rueda2_actual);

    return ruedas_reparadas;
}

int cantidad_conflictos_3_consecutivos(vector<int> fixture_rueda1, vector<int> fixture_rueda2){
    int cantidad_fechas = fixture_rueda1.size();
    int cantidad_conflictos = 0;
    int contador_local_consecutivo = 0;
    int contador_visita_consecutivo = 0;
    for (int i = 0; i < fixture_rueda1.size()*2-2; i++) { 

        if (i == 0){ // primera fecha rueda 1
            if (fixture_rueda1[0] > 0 && fixture_rueda1[1] > 0 && fixture_rueda1[2] > 0 || fixture_rueda1[0] < 0 && fixture_rueda1[1] < 0 && fixture_rueda1[2] < 0){
                cantidad_conflictos++;
            }

        }
        else if (i <= fixture_rueda1.size()-2){ // resto fechas rueda 1
            if (fixture_rueda1[i-1] > 0 && fixture_rueda1[i] > 0 && fixture_rueda1[i+1] > 0 || fixture_rueda1[i-1] < 0 && fixture_rueda1[i] < 0 && fixture_rueda1[i+1] < 0){
                cantidad_conflictos++;
            }
        }
        else if (i == fixture_rueda1.size()-1){ // ultima fecha rueda 1
            if (fixture_rueda1[cantidad_fechas-2] > 0 && fixture_rueda1[cantidad_fechas-1] > 0 && fixture_rueda2[0] > 0 || fixture_rueda1[cantidad_fechas-2] < 0 && fixture_rueda1[cantidad_fechas-1] < 0 && fixture_rueda2[0] < 0){
                cantidad_conflictos++;
            }
        }
        else if (i == fixture_rueda1.size()){ // primera fecha rueda 2
            if (fixture_rueda2[0] > 0 && fixture_rueda2[1] > 0 && fixture_rueda2[2] > 0 || fixture_rueda2[0] < 0 && fixture_rueda2[1] < 0 && fixture_rueda2[2] < 0){
                cantidad_conflictos++;
            }
        }
        else{ // resto de fechas rueda 2
            int fecha_rueda2 = i - fixture_rueda1.size();
            if (fixture_rueda2[fecha_rueda2-1] > 0 && fixture_rueda2[fecha_rueda2] > 0 && fixture_rueda2[fecha_rueda2+1] > 0 || fixture_rueda2[fecha_rueda2-1] < 0 && fixture_rueda2[fecha_rueda2] < 0 && fixture_rueda2[fecha_rueda2+1] < 0){
                cantidad_conflictos++;
            }
        }

        
    }
    // revisando breaks primeras dos y ultimas dos fechas
    if(fixture_rueda1[0] > 0 && fixture_rueda1[1] > 0 || fixture_rueda1[0] < 0 && fixture_rueda1[1] < 0){
        cantidad_conflictos++;
    }
    if(fixture_rueda1[cantidad_fechas-2] > 0 && fixture_rueda1[cantidad_fechas-1] > 0 || fixture_rueda1[cantidad_fechas-2] < 0 && fixture_rueda1[cantidad_fechas-1] < 0){
        cantidad_conflictos++;
    }
    
    return cantidad_conflictos;
}

vector<vector<vector<int>>> reparacion_ambas_ruedas_v2(vector<vector<int>> rueda1, vector<vector<int>> rueda2){
    vector<vector<vector<int>>> ruedas_reparadas;
    vector<vector<int>> rueda1_actual = rueda1;
    vector<vector<int>> rueda2_actual = rueda2;
    int cantidad_equipos = rueda1.size();
    int cantidad_fechas = rueda1[0].size();

    for (int i = 0; i < cantidad_equipos; i++) {
        //cout << "Revisando equipo " << i+1 << '\n';
        for (int fecha_r1 = 0; fecha_r1 < cantidad_fechas; fecha_r1++) {
            for (int fecha_r2 = 0; fecha_r2 < cantidad_fechas; fecha_r2++) {
                //cout << "Revisando fecha " << fecha_r1+1 << " y " << fecha_r2+1 << '\n';
                //bool conflicto_rueda1 = false;
                //bool conflicto_rueda2 = false;
                if (abs(rueda1_actual[i][fecha_r1]) == abs(rueda2_actual[i][fecha_r2])) { 
                    int rival = abs(rueda1_actual[i][fecha_r1]);
                    // equipo i se enfrenta a su rival en la fecha r1 en la rueda 1 y r2 en la rueda dos
                    // verificando si hay conflicto (es decir, si los enfrentamientos se dan en la misma condicion)
                    if (rueda1_actual[i][fecha_r1] > 0 && rueda2_actual[i][fecha_r2] > 0 || rueda1_actual[i][fecha_r1] < 0 && rueda2_actual[i][fecha_r2] < 0){ //hay conflicto

                        vector<int> fixture_t1_r1 = rueda1_actual[i];
                        vector<int> fixture_t2_r1 = rueda1_actual[rival-1];

                        vector<int> fixture_t1_r2 = rueda2_actual[i];
                        vector<int> fixture_t2_r2 = rueda2_actual[rival-1];

                        // opcion 1: equipo i local en primera rueda
                        vector<int> fixture_t1_r1_opcion1 = fixture_t1_r1;
                        vector<int> fixture_t2_r1_opcion1 = fixture_t2_r1;
                        vector<int> fixture_t1_r2_opcion1 = fixture_t1_r2;
                        vector<int> fixture_t2_r2_opcion1 = fixture_t2_r2;

                        fixture_t1_r1_opcion1[fecha_r1] = abs(fixture_t1_r1[fecha_r1]);
                        fixture_t2_r1_opcion1[fecha_r1] = abs(fixture_t2_r1[fecha_r1]) * (-1);

                        fixture_t1_r2_opcion1[fecha_r2] = abs(fixture_t1_r2[fecha_r2]) * (-1);
                        fixture_t2_r2_opcion1[fecha_r2] = abs(fixture_t2_r2[fecha_r2]);

                        

                        int conflictos_opcion1 = cantidad_conflictos_3_consecutivos(fixture_t1_r1_opcion1, fixture_t1_r2_opcion1) + cantidad_conflictos_3_consecutivos(fixture_t2_r1_opcion1, fixture_t2_r2_opcion1);

                        // opcion 2: equipo rival local en primera rueda
                        vector<int> fixture_t1_r1_opcion2 = fixture_t1_r1;
                        vector<int> fixture_t2_r1_opcion2 = fixture_t2_r1;
                        vector<int> fixture_t1_r2_opcion2 = fixture_t1_r2;
                        vector<int> fixture_t2_r2_opcion2 = fixture_t2_r2;

                        fixture_t1_r1_opcion2[fecha_r1] = abs(fixture_t1_r1[fecha_r1]) * (-1);
                        fixture_t2_r1_opcion2[fecha_r1] = abs(fixture_t2_r1[fecha_r1]);

                        fixture_t1_r2_opcion2[fecha_r2] = abs(fixture_t1_r2[fecha_r2]);
                        fixture_t2_r2_opcion2[fecha_r2] = abs(fixture_t2_r2[fecha_r2]) * (-1);

                        int conflictos_opcion2 = cantidad_conflictos_3_consecutivos(fixture_t1_r1_opcion2, fixture_t2_r1_opcion2) + cantidad_conflictos_3_consecutivos(fixture_t1_r2_opcion2, fixture_t2_r2_opcion2);

                        if(conflictos_opcion1 < conflictos_opcion2){
                            rueda1_actual[i] = fixture_t1_r1_opcion1;
                            rueda1_actual[rival-1] = fixture_t2_r1_opcion1;
                            rueda2_actual[i] = fixture_t1_r2_opcion1;
                            rueda2_actual[rival-1] = fixture_t2_r2_opcion1;
                        }
                        else{
                            rueda1_actual[i] = fixture_t1_r1_opcion2;
                            rueda1_actual[rival-1] = fixture_t2_r1_opcion2;
                            rueda2_actual[i] = fixture_t1_r2_opcion2;
                            rueda2_actual[rival-1] = fixture_t2_r2_opcion2;
                        }
                    }
                }
            }
        }
    }

    ruedas_reparadas.push_back(rueda1_actual);
    ruedas_reparadas.push_back(rueda2_actual);

    return ruedas_reparadas;
}

bool is_in_vector(vector<int> v, int x) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == x) {
            return true;
        }
    }
    return false;
}

//retorna el equipo que falta enfrentar en la fecha de revision (Lo retorna con el signo correspondiente)
int revision_rivales_equipo(int equipo, vector<int> rivales_actuales, int fecha_revision){

    //verificacion si el equipo en pos_revision ya es rival del equipo en otra fecha

    int equipo_revision = abs(rivales_actuales[fecha_revision-1]);

    for (int i=0; i<rivales_actuales.size(); i++){
        if(i != fecha_revision-1 && abs(rivales_actuales[i]) == equipo_revision){
            //hay conflicto
            //cout << "El equipo " << equipo << " se enfrenta al equipo " << equipo_revision << " en las fechas " << i+1 << " y " << fecha_revision <<"\n";
            
            //buscando al equipo que falta enfrentar
            for(int e=0;e<=rivales_actuales.size();e++){
                
                bool rival_encontrado = false;

                if (e+1 == equipo){ //no se busca el mismo equipo en los rivales
                    continue;   
                }
                else{
                    for (int j=0; j<rivales_actuales.size(); j++){
                        if (abs(rivales_actuales[j]) == e+1){rival_encontrado = true;}
                    }
                    if (!rival_encontrado){
                        //cout << "El equipo faltante es " << e+1 << '\n';
                        if (rivales_actuales[fecha_revision-1]>0){return e+1;}
                        else{return (e+1)*(-1);}
                    }
                }
            }
        }
    }
    //cout << "No hay conflictos\n";
    return 0;
}

//retorna true o flase si el equipo no esta asignado en esa fecha
bool equipo_faltante_fecha(vector<vector<int>> rueda, int fecha, int equipo){
    for(int i=0; i<rueda.size(); i++){
        if (abs(rueda[i][fecha-1]) == equipo){
            return false;
        }
    }
    return true;
}

bool es_casilla_fija(vector<vector<int>> casillas_fijas, int equipo, int fecha){
    for (int i=0; i<casillas_fijas.size(); i++){
        if (casillas_fijas[i][0] == equipo && casillas_fijas[i][1] == fecha){
            return true;
        }
    }
    return false;
}

// Invierte las localias de los equipos t1 y t2
vector<vector<int>> SwapHomes(vector<vector<int>>rueda, int t1, int t2) {

    //cout << "Se realiza un swap de localias entre los equipos " << t1 << " y " << t2 << '\n';

    vector<vector<int>> rueda_aux = rueda;
    int cambios = 0;
    int cant_fechas = rueda.size();
    int cant_equipos = rueda[0].size();
    for (int fecha = 0; fecha <= cant_fechas; fecha++) {
        for (int equipo = 0; equipo <= cant_equipos; equipo++){
            //cout << "equipo: " << equipo + 1 << " fecha: " << fecha + 1 << " valor: " << calendarizacion[equipo][fecha] << '\n';

            //t1 vs t2 cambia a t2 vs t1
            if (equipo + 1 == t1 && rueda[equipo][fecha] == t2 ){
                //cout << "Se encontro que se disputa " << t1 << " vs " << t2 <<  " en la fecha " << fecha + 1 << '\n';
                rueda_aux[equipo][fecha] = -rueda[equipo][fecha];
                cambios++;
                if (cambios == 2) {
                    return rueda_aux;
                }
            }
            //t2 vs t1 cambia a t1 vs t2
            else if(equipo + 1 == t2 && rueda[equipo][fecha] == -t1){
                //cout << "Se encontro que se disputa " << t1 << " vs " << t2 <<  " en la fecha " << fecha + 1 << '\n';
                rueda_aux[equipo][fecha] = -rueda[equipo][fecha];
                cambios++;
                if (cambios == 2) {
                    return rueda_aux;
                }
            }

            //cambiando rival de t1 a -t2
            else if (equipo + 1 == t1 && rueda[equipo][fecha] == -t2) {
                //cout << "Se encontro que se disputa " << t2 << " vs " << t1 <<  " en la fecha " << fecha + 1 << '\n';
                rueda_aux[equipo][fecha] = -rueda[equipo][fecha];
                cambios++;
                if (cambios == 2) {
                    return rueda_aux;
                }
            }
            //cambiando rival de t2 a -t1
            else if (equipo + 1 == t2 && rueda[equipo][fecha] == t1){
                rueda_aux[equipo][fecha] = -rueda[equipo][fecha];
                cambios++;
                if (cambios == 2) {
                    return rueda_aux;
                }
            }
        }
    }
    return rueda_aux;
}

// Intercambia todo el fixture de los equipos t1 y t2 EN UNA RUEDA
vector<vector<int>> SwapTeams(vector<vector<int>>rueda, int t1, int t2) {
    vector<int> fixture_t1 = rueda[t1 - 1];
    vector<int> fixture_t2 = rueda[t2 - 1];
    vector<vector<int>> rueda_aux = rueda;

    int cantidad_equipos = rueda.size();
    int cantidad_fechas = cantidad_equipos - 1;

    //se intercambia el fixture de ambos equipos
    for(int i=0; i<cantidad_fechas; i++){
        if(rueda[t1 - 1][i] == t2 || rueda[t1 - 1][i] == -t2){
            continue;
        }
        else{
            rueda_aux[t1 - 1][i] = fixture_t2[i];
            rueda_aux[t2 - 1][i] = fixture_t1[i];
        }
    }

    //se corrige el fixture en las demas filas
    for(int i=0; i<cantidad_equipos; i++){
        if (i == t1 - 1 || i == t2 - 1){
            continue;
        }
        else{
            //cout << "Fila diferente a t1 y t2\n";
            for(int j=0; j < cantidad_fechas; j++){
                if(rueda[i][j] == t1){
                    rueda_aux[i][j] = t2;
                    //cout << "cambiando t1 por t2\n";
                }
                else if(rueda[i][j] == -t1){
                    rueda_aux[i][j] = -t2;
                    //cout << "cambiando -t1 por -t2\n";
                }
                else if(rueda[i][j] == t2){
                    rueda_aux[i][j] = t1;
                    //cout << "cambiando t2 por t1\n";
                }
                else if(rueda[i][j] == -t2){
                    rueda_aux[i][j] = -t1;
                    //cout << "cambiando -t2 por -t1\n";
                }
            }
        }
    }
    return rueda_aux;
}

// Intercambia todo los enfrentamientos de la ronda r1 y r2 (r1<r2)
vector<vector<int>> SwapRounds(vector<vector<int>>rueda, int r1, int r2) {
    vector<vector<int>> rueda_aux = rueda;

    int cantidad_equipos = rueda.size();
    int cantidad_fechas = rueda[0].size();

    for(int j=0; j<cantidad_fechas; j++){
        if (j == r1 - 1){
            for(int i=0; i<cantidad_equipos; i++){
                rueda_aux[i][j] = rueda[i][r2 - 1];
            }
        }
        else if(j == r2 - 1){
            for(int i=0; i<cantidad_equipos; i++){
                rueda_aux[i][j] = rueda[i][r1 - 1];
            }
        }
        else{
            continue;
        }
    }
    return rueda_aux;   
}

// Intercambia los rivales de los equipos t1 y t2 en la ronda r
vector<vector<int>> SwapMatches(vector<vector<int>> rueda, int t1, int t2, int r) {
    vector<vector<int>> rueda_aux = rueda;
    int cantidad_equipos = rueda.size();
    int cantidad_fechas = rueda[0].size();

    vector<vector<int>> casillas_fijas;

    //si t1 y t2 ya se enfrentan en la fecha r, no se hace nada
    if(abs(rueda[t1-1][r-1])==t2){
        return rueda;
    }

    int rival_original_t1 = abs(rueda[t1 - 1][r - 1]); //t3
    int rival_original_t2 = abs(rueda[t2 - 1][r - 1]); //t4

    //cout << "t3: " << rival_original_t1 << '\n';
    //cout << "t4: " << rival_original_t2 << '\n';

    int r1; // fecha original donde se enfrentan t1 y t4
    int r2; // fecha original donde se enfrentan t2 y t3

    for (int i=0; i<rueda[t1-1].size(); i++){
        if (abs(rueda[t1-1][i]) == rival_original_t2 ){
            r1=i+1;
            //cout << "r1: " << r1 << '\n';
            break;
        }
    }

    for (int i=0; i<rueda[t2-1].size(); i++){
        if (abs(rueda[t2-1][i]) == rival_original_t1 ){
            r2=i+1;
            //cout << "r2: " << r2 << '\n';
            break;
        }
    }
    
    //ahora en r, se va a jugar t1 vs t4 y t2 vs t3
    //t1 y t2 mantienen su condicion de local o visita mientras que su rival se adapta

    if (rueda[t1 - 1][r - 1] > 0) {
        rueda_aux[t1 - 1][r - 1] = rival_original_t2;
        rueda_aux[rival_original_t2 - 1][r - 1] = -t1;
    }
    else {
        rueda_aux[t1 - 1][r - 1] = -rival_original_t2;
        rueda_aux[rival_original_t2 - 1][r - 1] = t1;
    }

    casillas_fijas.push_back({t1-1, r-1});
    casillas_fijas.push_back({rival_original_t2-1, r-1});

    if (rueda[t2 - 1][r - 1] > 0) {
        rueda_aux[t2 - 1][r - 1] = rival_original_t1;
        rueda_aux[rival_original_t1 - 1][r - 1] = -t2;
    }
    else {
        rueda_aux[t2 - 1][r - 1] = -rival_original_t1;
        rueda_aux[rival_original_t1 - 1][r - 1] = t2;
    }

    casillas_fijas.push_back({t2-1, r-1});
    casillas_fijas.push_back({rival_original_t1-1, r-1});

    if (rueda[t1-1][r1-1]>0){
        rueda_aux[t1-1][r1-1] = rival_original_t1;
    }
    else{
        rueda_aux[t1-1][r1-1] = -rival_original_t1;
    }

    if (rueda[t2-1][r2-1]>0){
        rueda_aux[t2-1][r2-1] = rival_original_t2;
    }
    else{
        rueda_aux[t2-1][r2-1] = -rival_original_t2;
    }

    if (rueda[rival_original_t2-1][r1-1]>0){
        rueda_aux[rival_original_t2-1][r1-1] = t2;
    }
    else{
        rueda_aux[rival_original_t2-1][r1-1] = -t2;
    }

    if (rueda[rival_original_t1-1][r2-1]>0){
        rueda_aux[rival_original_t1-1][r2-1] = t1;
    }
    else{
        rueda_aux[rival_original_t1-1][r2-1] = -t1;
    }

    //se revisan en paralelo las rondas r1 y r2

    //cout << "Antes de primera correccion en las demas fechas \n";

    //print_rueda(rueda_aux);

    for(int i=0; i<rueda.size(); i++){
        if(equipo_faltante_fecha(rueda_aux, r1, abs(rueda_aux[i][r2-1])) || equipo_faltante_fecha(rueda_aux, r2, abs(rueda_aux[i][r1-1]))){
            //cout << "equipo faltante en la fecha " << r1 << ": " << i+1 << '\n';
            //cout << "se realiza un cambio en la fecha " << r1 << " y " << r2 << " del equipo " << i+1 << '\n';
            int equipo_aux = rueda_aux[i][r2-1];
            rueda_aux[i][r2-1] = rueda_aux[i][r1-1];
            rueda_aux[i][r1-1] = equipo_aux;
        }
    }

    //cout << "Luego de swaps entre ambas rondas \n";
    //print_rueda(rueda_aux);

    //Revision de consistencia por fecha (se verifica que si a enfrenta a b, entonces b enfrenta a a)
    
    int ronda_actual;

    int rival_equipo_actual;

    vector<int> equipos_asignados_esta_fecha;
    vector<int> rondas = {r1, r2};

    int equipo_sin_asignar1=0, equipo_sin_asignar2;

    for(int r=0; r<2;r++){

        ronda_actual = rondas[r];

        equipo_sin_asignar1 = 0;
        equipo_sin_asignar2 = 0;

        //cout << "ronda actual: " << ronda_actual << '\n';

            equipos_asignados_esta_fecha = {};

            for (int i=0; i < cantidad_equipos; i++){

                //cout << "revisando equipo " << i+1 << " ronda " << ronda_actual << '\n';

                rival_equipo_actual = abs(rueda_aux[i][ronda_actual-1]);
                // caso donde los equipos se enfrentan pero las localias estan mal
                if(abs(rueda_aux[rival_equipo_actual-1][ronda_actual-1]) == i+1 && (rueda_aux[rival_equipo_actual-1][ronda_actual-1] < 0 && rueda_aux[i][ronda_actual-1] < 0 || rueda_aux[rival_equipo_actual-1][ronda_actual-1] > 0 && rueda_aux[i][ronda_actual-1] > 0)){
                    // por defecto se cambia la localia del equipo rival
                    rueda_aux[rival_equipo_actual-1][ronda_actual-1] = -i-1;
                    //cout << "se cambia la localia del equipo " << rival_equipo_actual << " en la fecha " << ronda_actual << '\n';
                }
                else if (abs(rueda_aux[rival_equipo_actual-1][ronda_actual-1]) != i+1){
                    //cout << "el equipo " << i+1 << " se enfrenta a " << rival_equipo_actual << " en la fecha " << ronda_actual << " pero no viceversa\n";

                    if (!is_in_vector(equipos_asignados_esta_fecha,rival_equipo_actual)){ // si el rival del equipo i+1 no ha sido asignado

                        //cout << "asignando equipos " << i+1 << " y " << rival_equipo_actual << '\n';

                        if(rueda_aux[i][ronda_actual-1] > 0){
                            rueda_aux[rival_equipo_actual-1][ronda_actual-1] = -i-1;
                        }
                        else{
                            rueda_aux[rival_equipo_actual-1][ronda_actual-1] = i+1;
                        }

                        equipos_asignados_esta_fecha.push_back(abs(rival_equipo_actual));
                        equipos_asignados_esta_fecha.push_back(i+1);
                    }
                }
                else{
                    if ((rueda_aux[i][ronda_actual-1] > 0 && rueda_aux[rival_equipo_actual-1][ronda_actual-1] > 0) || (rueda_aux[i][ronda_actual-1] < 0 && rueda_aux[rival_equipo_actual-1][ronda_actual-1]< 0)){
                        rueda_aux[rival_equipo_actual-1][ronda_actual-1] = -i-1;
                    }
                    if (!is_in_vector(equipos_asignados_esta_fecha, i+1) && !is_in_vector(equipos_asignados_esta_fecha, abs(rival_equipo_actual))){
                        equipos_asignados_esta_fecha.push_back(abs(rival_equipo_actual));
                        equipos_asignados_esta_fecha.push_back(i+1);
                        //cout << "el equipo " << i+1 << " se enfrenta a " << rival_equipo_actual << " en la fecha " << ronda_actual << " y viceversa\n";
                    }
                }
            }

            //asignado dos equipos restantes sin asignar en la fecha actual

            if (equipos_asignados_esta_fecha.size()==cantidad_equipos-2){

                for (int i=0; i<cantidad_equipos; i++){
                    if (!is_in_vector(equipos_asignados_esta_fecha, i+1)){
                        if (equipo_sin_asignar1 == 0){
                            equipo_sin_asignar1 = i+1;
                        }
                        else{
                            equipo_sin_asignar2 = i+1;
                        }
                    }
                }
                //cout << "equipos sin asignar en la fecha " << ronda_actual << ": " << equipo_sin_asignar1 << " y " << equipo_sin_asignar2 << '\n';
                if (rueda_aux[equipo_sin_asignar1-1][ronda_actual-1] > 0 && rueda_aux[equipo_sin_asignar2-1][ronda_actual-1] < 0){
                    rueda_aux[equipo_sin_asignar1-1][ronda_actual-1] = equipo_sin_asignar2;
                    rueda_aux[equipo_sin_asignar2-1][ronda_actual-1] = -equipo_sin_asignar1;
                }
                else if(rueda_aux[equipo_sin_asignar1-1][ronda_actual-1] < 0 && rueda_aux[equipo_sin_asignar2-1][ronda_actual-1] > 0){
                    rueda_aux[equipo_sin_asignar1-1][ronda_actual-1] = -equipo_sin_asignar2;
                    rueda_aux[equipo_sin_asignar2-1][ronda_actual-1] = equipo_sin_asignar1;
                }
                else{
                    rueda_aux[equipo_sin_asignar1-1][ronda_actual-1] = equipo_sin_asignar2;
                    rueda_aux[equipo_sin_asignar2-1][ronda_actual-1] = -equipo_sin_asignar1;
                }
        }
    }
    bool conflictos = true;
    int contador_sin_conflictos = 0; //si llega al largo de una fila sin conflictos, se termina el ciclo
    int fecha_actual = 1; //se comienza desde la ronda 1
    int rival_faltante, equipo_en_revision, equipos_revisados;
    bool conflicto_fecha_actual, revision_equipos_fecha_completa;

    //vector<int> equipos_asignados_esta_fecha;

    int contador_ciclos = 0;
    //se cuenta por fecha, si se dan 10 vueltas y aun hay conclifots se termina el ciclo

    while (conflictos)
    {

        if (contador_ciclos > cantidad_fechas*10)
        {
            //cout << "No se pudieron corregir conlfictos \n";
            return rueda; //no se hacen cambios
        }

        //cout << "LOOP1\n";

        conflicto_fecha_actual = false;
        //revision_equipos_fecha_completa = false;

        equipos_asignados_esta_fecha = {};
        equipos_revisados = 0;

        //cout << "fecha actual: " << fecha_actual << '\n';
        
        for (int i=0; i<cantidad_equipos;i++){

            //cout << "LOOP2\n";       

            rival_faltante = revision_rivales_equipo(i+1, rueda_aux[i], fecha_actual);

            //cout << "rival faltante: " << rival_faltante << '\n';
            //cout << " Esta en equipos asignaods: " << is_in_vector(equipos_asignados_esta_fecha, i+1) << '\n';

            if (rival_faltante !=0 && is_in_vector(equipos_asignados_esta_fecha, i+1)==0){// si hay conflicto y el equipo no ha sido reasignado en este fecha
                conflicto_fecha_actual = true;
                //std::cout << "conflicto en la fecha " << fecha_actual << " con el equipo " << i+1 << '\n';

                if (!es_casilla_fija(casillas_fijas, i, fecha_actual-1) && !es_casilla_fija(casillas_fijas, abs(rival_faltante)-1, fecha_actual-1)){
                    //std::cout << "cambiando al equipo " << rueda_aux[i][fecha_actual-1] << " por el equipo " << rival_faltante << '\n';

                    rueda_aux[i][fecha_actual-1] = rival_faltante;

                    if (rival_faltante>0){
                        rueda_aux[abs(rival_faltante)-1][fecha_actual-1] = -i-1;
                    }
                    else{
                        rueda_aux[abs(rival_faltante)-1][fecha_actual-1] = i+1;
                    }

                    equipos_asignados_esta_fecha.push_back(i+1);
                    equipos_asignados_esta_fecha.push_back(abs(rival_faltante));

                }
                else{
                    //std::cout << "casilla fija en fila " << i << " columna " << fecha_actual-1 << "\n";
                    equipos_revisados++; //CAMBIO PARA COREGIR EL ERROR DE QUE NO SE AVANZABA DE FECHA
                    equipos_revisados++; //CAMBIO PARA COREGIR EL ERROR DE QUE NO SE AVANZABA DE FECHA
                    //equipos_asignados_esta_fecha.push_back(i+1);
                }

            }
            else{
                equipos_revisados++;
            }
        }

       int equipo_con_conflicto_1 = 0;
       int equipo_con_conflicto_2 = 0;

        for (int i=0; i<cantidad_equipos; i++){

            //cout << "LOOP3\n";

            int rival_equipo_i = abs(rueda_aux[i][fecha_actual-1]);
            //cout << "rival equipo " << i+1 << " en fecha " << fecha_actual << ": " << rival_equipo_i << '\n';
            //cout << "rival equipo " << rival_equipo_i << " en fecha " << fecha_actual << ": " << abs(rueda_aux[rival_equipo_i-1][fecha_actual-1]) << '\n';
            //cout << abs(rueda_aux[rival_equipo_i][fecha_actual-1]) << "\n";
            
            if ((i+1) != abs(rueda_aux[rival_equipo_i-1][fecha_actual-1])){
                //cout << "El equipo " << i+1 << " se enfrenta al equipo " << rival_equipo_i << " en la fecha " << fecha_actual << '\n';
                //cout << "Sin embrago, el equipo " << rival_equipo_i << " se enfrenta al equipo " << abs(rueda_aux[rival_equipo_i-1][fecha_actual-1]) << " en la fecha " << fecha_actual << '\n';

                if (equipo_con_conflicto_1 == 0){
                    equipo_con_conflicto_1 = i+1;
                }
                else{
                    equipo_con_conflicto_2 = i+1;
                }
            }
        }
        //cout << "equipos co conflicto en la fecha " << fecha_actual << ": " << equipo_con_conflicto_1 << " y " << equipo_con_conflicto_2 << '\n';
        
        if (equipo_con_conflicto_1 != 0 && equipo_con_conflicto_2 != 0){
            //cout << "cambiando al equipo " << equipo_con_conflicto_1 << " por el equipo " << equipo_con_conflicto_2 << '\n';

            // si los signos son diferentes, se mantienen los signos
            if (rueda_aux[equipo_con_conflicto_1-1][fecha_actual-1] > 0 && rueda_aux[equipo_con_conflicto_2-1][fecha_actual-1] < 0){
                rueda_aux[equipo_con_conflicto_1-1][fecha_actual-1] = equipo_con_conflicto_2;
                rueda_aux[equipo_con_conflicto_2-1][fecha_actual-1] = -equipo_con_conflicto_1;
            }
            else if (rueda_aux[equipo_con_conflicto_1-1][fecha_actual-1] < 0 && rueda_aux[equipo_con_conflicto_2-1][fecha_actual-1] > 0){
                rueda_aux[equipo_con_conflicto_1-1][fecha_actual-1] = -equipo_con_conflicto_2;
                rueda_aux[equipo_con_conflicto_2-1][fecha_actual-1] = equipo_con_conflicto_1;
            }
            else{
                rueda_aux[equipo_con_conflicto_1-1][fecha_actual-1] = equipo_con_conflicto_2;
                rueda_aux[equipo_con_conflicto_2-1][fecha_actual-1] = -equipo_con_conflicto_1;

            }

            equipos_revisados = equipos_revisados + 2;
        }

        //print_rueda(rueda_aux);
        

        //verificacion de conflictos en fecha actual
        if (conflicto_fecha_actual){
            contador_sin_conflictos = 0;
        }
        else{
            contador_sin_conflictos++;
        }

        //ya se recorrio toda la rueda sin conlfictos
        if (contador_sin_conflictos == cantidad_equipos+1){
            conflictos = false;
        }

        //se avanza a la siguiente fecha
        //cout << "equipos revisados: " << equipos_revisados << '\n';
        //cout << "cantidad de equipos: " << cantidad_equipos << '\n';
        if (equipos_revisados >= cantidad_equipos){ //CAMBIO PARA COREGIR EL ERROR DE QUE NO SE AVANZABA DE FECHA
            //cout << "revision completa de la fecha " << fecha_actual << '\n';
            if(fecha_actual >= cantidad_fechas){
                fecha_actual = 1;
            }
            else{
                fecha_actual++;
            }
            //return rueda_aux; // ESTO ES PARA PROBAR; LUEGO HAY QUE ELIMINARLO
        }

        //print_rueda(rueda_aux);
        contador_ciclos++;
    }



    return rueda_aux;
}

// Intercambia los rivales de los equipos de t1 en la ronda r1 con los de r2
vector<vector<int>> SwapMatchRound(vector<vector<int>> rueda, int t1, int r1, int r2) {
    int cantidad_equipos = rueda.size();
    int cantidad_fechas = rueda[0].size();

    int t2 = abs(rueda[t1 - 1][r1 - 1]); //rival original de t1 en r1
    int t3 = abs(rueda[t1 - 1][r2 - 1]); //rival original de t1 en r2
    int rival_t3_r1 = abs(rueda[t3 - 1][r1 - 1]); 
    int rival_t2_r2 = abs(rueda[t2 - 1][r2 - 1]);
    vector<vector<int>> rueda_aux = rueda;

    vector<vector<int>> casillas_fijas;

    //cout << "t1: " << t1 << " t2: " << t2 << " t3: " << t3 << " rival_t3_r1: " << rival_t3_r1 << " rival_t2_r2: " << rival_t2_r2 << '\n';

    //reagendando r1
    if (rueda[t1 - 1][r1 - 1]>0){
        rueda_aux[t1 - 1][r1 - 1] = t3;
        rueda_aux[t3 - 1][r1 - 1] = -t1;

    }
    else{
        rueda_aux[t1 - 1][r1 - 1] = -t3;
        rueda_aux[t3 - 1][r1 - 1] = t1;
    }

    casillas_fijas.push_back({t1-1, r1-1});
    casillas_fijas.push_back({t3-1, r1-1});

    if (rueda[t2 - 1][r1 - 1]>0){
        rueda_aux[t2 - 1][r1 - 1] = rival_t3_r1;
        rueda_aux[rival_t3_r1 - 1][r1 - 1] = -t2;
    }
    else{
        rueda_aux[t2 - 1][r1 - 1] = -rival_t3_r1;
        rueda_aux[rival_t3_r1 - 1][r1 - 1] = t2;
    }

    //reagendando r2
    if (rueda[t1 - 1][r2 - 1]>0){
        rueda_aux[t1 - 1][r2 - 1] = t2;
        rueda_aux[t2 - 1][r2 - 1] = -t1;
    }
    else{
        rueda_aux[t1 - 1][r2 - 1] = -t2;
        rueda_aux[t2 - 1][r2 - 1] = t1;
    }

    casillas_fijas.push_back({t1-1, r2-1});
    casillas_fijas.push_back({t2-1, r2-1});
    
    if (rueda[t3 - 1][r2 - 1]>0){
        rueda_aux[t3 - 1][r2 - 1] = rival_t2_r2;
        rueda_aux[rival_t2_r2 - 1][r2 - 1] = -t3;
    }
    else{
        rueda_aux[t3 - 1][r2 - 1] = -rival_t2_r2;
        rueda_aux[rival_t2_r2 - 1][r2 - 1] = t3;
    }

    //ciclo de reparacion de inconsistencias en el resto del fixture
    //se comienza desde la ronda siguiente a r2

    
    bool conflictos = true;
    int contador_sin_conflictos = 0; //si llega al largo de una fila sin conflictos, se termina el ciclo
    int fecha_actual = r2+1; //se comienza desde la ronda siguiente a r2
    int rival_faltante, equipo_en_revision, equipos_revisados;
    bool conflicto_fecha_actual, revision_equipos_fecha_completa;

    //se comienza desde la ronda siguiente a r2
    if (fecha_actual > cantidad_fechas){
        fecha_actual = 1;
    }

    vector<int> equipos_asignados_esta_fecha = {};
    
    int contador_ciclos = 0;

    while (conflictos)
    {

        contador_ciclos++;

        if (contador_ciclos > cantidad_fechas*10)
        {
            //cout << "No se pudieron corregir conlfictos \n";
            return rueda; //no se hacen cambios
        }

        //cout << "LOOP1\n";

        conflicto_fecha_actual = false;
        //revision_equipos_fecha_completa = false;

        equipos_asignados_esta_fecha = {};
        equipos_revisados = 0;

        //cout << "fecha actual: " << fecha_actual << '\n';
        
        for (int i=0; i<cantidad_equipos;i++){

            //cout << "LOOP2\n";       

            rival_faltante = revision_rivales_equipo(i+1, rueda_aux[i], fecha_actual);

            //cout << "rival faltante: " << rival_faltante << '\n';
            //cout << " Esta en equipos asignaods: " << is_in_vector(equipos_asignados_esta_fecha, i+1) << '\n';

            if (rival_faltante !=0 && is_in_vector(equipos_asignados_esta_fecha, i+1)==0){// si hay conflicto y el equipo no ha sido reasignado en este fecha
                conflicto_fecha_actual = true;
                //std::cout << "conflicto en la fecha " << fecha_actual << " con el equipo " << i+1 << '\n';

                if (!es_casilla_fija(casillas_fijas, i, fecha_actual-1) && !es_casilla_fija(casillas_fijas, abs(rival_faltante)-1, fecha_actual-1)){
                    //std::cout << "cambiando al equipo " << rueda_aux[i][fecha_actual-1] << " por el equipo " << rival_faltante << '\n';

                    rueda_aux[i][fecha_actual-1] = rival_faltante;

                    if (rival_faltante>0){
                        rueda_aux[abs(rival_faltante)-1][fecha_actual-1] = -i-1;
                    }
                    else{
                        rueda_aux[abs(rival_faltante)-1][fecha_actual-1] = i+1;
                    }

                    equipos_asignados_esta_fecha.push_back(i+1);
                    equipos_asignados_esta_fecha.push_back(abs(rival_faltante));

                }
                else{
                    //std::cout << "casilla fija en fila " << i << " columna " << fecha_actual-1 << "\n";
                    equipos_revisados++; //CAMBIO PARA COREGIR EL ERROR DE QUE NO SE AVANZABA DE FECHA
                    equipos_revisados++; //CAMBIO PARA COREGIR EL ERROR DE QUE NO SE AVANZABA DE FECHA
                    //equipos_asignados_esta_fecha.push_back(i+1);
                }

            }
            else{
                equipos_revisados++;
            }
        }

       int equipo_con_conflicto_1 = 0;
       int equipo_con_conflicto_2 = 0;

        for (int i=0; i<cantidad_equipos; i++){

            //cout << "LOOP3\n";

            int rival_equipo_i = abs(rueda_aux[i][fecha_actual-1]);
            //cout << "rival equipo " << i+1 << " en fecha " << fecha_actual << ": " << rival_equipo_i << '\n';
            //cout << "rival equipo " << rival_equipo_i << " en fecha " << fecha_actual << ": " << abs(rueda_aux[rival_equipo_i-1][fecha_actual-1]) << '\n';
            //cout << abs(rueda_aux[rival_equipo_i][fecha_actual-1]) << "\n";
            
            if ((i+1) != abs(rueda_aux[rival_equipo_i-1][fecha_actual-1])){
                //cout << "El equipo " << i+1 << " se enfrenta al equipo " << rival_equipo_i << " en la fecha " << fecha_actual << '\n';
                //cout << "Sin embrago, el equipo " << rival_equipo_i << " se enfrenta al equipo " << abs(rueda_aux[rival_equipo_i-1][fecha_actual-1]) << " en la fecha " << fecha_actual << '\n';

                if (equipo_con_conflicto_1 == 0){
                    equipo_con_conflicto_1 = i+1;
                }
                else{
                    equipo_con_conflicto_2 = i+1;
                }
            }
        }
        //cout << "equipos co conflicto en la fecha " << fecha_actual << ": " << equipo_con_conflicto_1 << " y " << equipo_con_conflicto_2 << '\n';
        
        if (equipo_con_conflicto_1 != 0 && equipo_con_conflicto_2 != 0){
            //cout << "cambiando al equipo " << equipo_con_conflicto_1 << " por el equipo " << equipo_con_conflicto_2 << '\n';

            // si los signos son diferentes, se mantienen los signos
            if (rueda_aux[equipo_con_conflicto_1-1][fecha_actual-1] > 0 && rueda_aux[equipo_con_conflicto_2-1][fecha_actual-1] < 0){
                rueda_aux[equipo_con_conflicto_1-1][fecha_actual-1] = equipo_con_conflicto_2;
                rueda_aux[equipo_con_conflicto_2-1][fecha_actual-1] = -equipo_con_conflicto_1;
            }
            else if (rueda_aux[equipo_con_conflicto_1-1][fecha_actual-1] < 0 && rueda_aux[equipo_con_conflicto_2-1][fecha_actual-1] > 0){
                rueda_aux[equipo_con_conflicto_1-1][fecha_actual-1] = -equipo_con_conflicto_2;
                rueda_aux[equipo_con_conflicto_2-1][fecha_actual-1] = equipo_con_conflicto_1;
            }
            else{
                rueda_aux[equipo_con_conflicto_1-1][fecha_actual-1] = equipo_con_conflicto_2;
                rueda_aux[equipo_con_conflicto_2-1][fecha_actual-1] = -equipo_con_conflicto_1;

            }

            equipos_revisados = equipos_revisados + 2;
        }

        //print_rueda(rueda_aux);
        

        //verificacion de conflictos en fecha actual
        if (conflicto_fecha_actual){
            contador_sin_conflictos = 0;
        }
        else{
            contador_sin_conflictos++;
        }

        //ya se recorrio toda la rueda sin conlfictos
        if (contador_sin_conflictos == cantidad_equipos+1){
            conflictos = false;
        }

        //se avanza a la siguiente fecha
        //cout << "equipos revisados: " << equipos_revisados << '\n';
        //cout << "cantidad de equipos: " << cantidad_equipos << '\n';
        if (equipos_revisados >= cantidad_equipos){ //CAMBIO PARA COREGIR EL ERROR DE QUE NO SE AVANZABA DE FECHA
            //cout << "revision completa de la fecha " << fecha_actual << '\n';
            if(fecha_actual >= cantidad_fechas){
                fecha_actual = 1;
            }
            else{
                fecha_actual++;
            }
            //return rueda_aux; // ESTO ES PARA PROBAR; LUEGO HAY QUE ELIMINARLO
        }
    }

    return rueda_aux;
}