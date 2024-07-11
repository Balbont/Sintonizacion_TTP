#include <iostream>
#include <vector>
#include "operadores.cpp"
using namespace std;


//GENERICAS

// fechas anteriores a torneos internacionales
// fechas posteriores a torneos internacionales

// retorna la cantidad de equipos en ese torneo que se enfrentan a equipos fuertes en las fechas internacionales indicadas
// C102b C102c C102d C102e C102f
int equipo_fuerte_fecha_internacional(vector<vector<int>> rueda1, vector<vector<int>> rueda2, vector<int> equipos_fuertes, vector<int> equipos_internacional, vector<int> fechas_internacionales){
    
    int cantidad = 0;
    int rival;
    vector<int> equipos_con_conflicto;

    for (int i = 0; i < equipos_internacional.size(); i++)
    {
        for (int j = 0; j < fechas_internacionales.size(); j++){

            if (fechas_internacionales[j] <= rueda1[0].size()){ // fecha esta en la primera rueda
                //rueda_fecha = 1;
                rival = abs(rueda1[equipos_internacional[i]-1][fechas_internacionales[j]-1]);
            }
            else{ // fecha esta en la segunda rueda
                //rueda_fecha = 2;
                //fechas_internacionales[j] = fechas_internacionales[j] - rueda1[0].size();
                rival = abs(rueda2[equipos_internacional[i]-1][fechas_internacionales[j]-1-rueda1[0].size()]);
            }

            for(int k = 0; k< equipos_fuertes.size(); k++){
                if (rival == equipos_fuertes[k]){
                    cantidad++;
                    equipos_con_conflicto.push_back(equipos_internacional[i]);
                }
            }   
        }
    }
    return cantidad;
}


// implementar fechas de distancia entre dos equipos
// retorna la cantidad de veces que dos equipos se enfrentan nuevamente sin considerar la diferencia de fechas
// C19
int distancia_fecha_enfrentarse_nuevamente(vector<vector<int>> rueda1, vector<vector<int>> rueda2, int minima_diferencia){

    int distancia = minima_diferencia/2;
    int inicio_rueda_1 = rueda1[0].size() - minima_diferencia/2;

    
    vector<int> equipos_con_conflicto;
    int cantidad_conflicto = 0;
    int cant_fechas_rueda = rueda1[0].size();
    int cant_equipos = rueda1.size();
    //int pos_revision = cant_fechas_rueda - minima_diferencia;
    //int numero_posiciones_a_revisar;

    for (int i = 0; i < cant_equipos; i++){

        for(int j = inicio_rueda_1; j < cant_fechas_rueda; j++){
            for(int k = 0; k < distancia; k++){
                if (abs(rueda1[i][j]) == abs(rueda2[i][k])){
                    //cout << "Equipo " << i+1 << " se enfrenta a " << abs(rueda1[i][j]) << " en la fecha " << j+1 << " y en la fecha " << k+1 << " de la segunda rueda" << endl;
                    cantidad_conflicto++;
                    if (is_in_vector(equipos_con_conflicto, i+1) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                        equipos_con_conflicto.push_back(i+1);
                    }
                }
            }
        }
    }

    return cantidad_conflicto;    
}

//veces que un equipo juega mas de dos partidos consecutivos de local
//C13
int local_3partidos(vector<vector<int>> rueda1, vector<vector<int>> rueda2){
    int cantidad_conflictos = 0;
    vector<int> equipos_con_conflictos;

    for (int i = 0; i < rueda1.size(); i++){

        //revision primera rueda
        for (int j = 0; j < rueda1[0].size()-2; j++){
            if (rueda1[i][j] > 0 && rueda1[i][j+1] > 0 && rueda1[i][j+2] > 0){
                cantidad_conflictos++;
                if (is_in_vector(equipos_con_conflictos, i+1) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                    equipos_con_conflictos.push_back(i+1);
                }
            }
        }

        //revision fechas entre ruedas
        if (rueda1[i][rueda1[0].size()-2] > 0 && rueda1[i][rueda1[0].size()-1] > 0 && rueda2[i][0] > 0){
            cantidad_conflictos++;
            if (is_in_vector(equipos_con_conflictos, i+1) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                equipos_con_conflictos.push_back(i+1);
            }
        }

        if (rueda1[i][rueda1[0].size()-1] > 0 && rueda2[i][0] > 0 && rueda2[i][1] > 0){
            cantidad_conflictos++;
            if (is_in_vector(equipos_con_conflictos, i+1) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                equipos_con_conflictos.push_back(i+1);
            }
        }

        //revisando segunda rueda

        for (int j = 0; j < rueda2[0].size()-2; j++){
            if (rueda2[i][j] > 0 && rueda2[i][j+1] > 0 && rueda2[i][j+2] > 0){
                cantidad_conflictos++;
                if (is_in_vector(equipos_con_conflictos, i+1) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                    equipos_con_conflictos.push_back(i+1);
                }
            }
        }
    }
    return cantidad_conflictos;
}

//veces que un equipo juega mas de dos partidos consecutivos de visitante
// C14
int visitante_3partidos(vector<vector<int>> rueda1, vector<vector<int>> rueda2){
    int cantidad_conflictos = 0;
    vector<int> equipos_con_conflictos;

    for (int i = 0; i < rueda1.size(); i++){

        //revision primera rueda
        for (int j = 0; j < rueda1[0].size()-2; j++){
            if (rueda1[i][j] < 0 && rueda1[i][j+1] < 0 && rueda1[i][j+2] < 0){
                cantidad_conflictos++;
                if (is_in_vector(equipos_con_conflictos, i+1) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                    equipos_con_conflictos.push_back(i+1);
                }
            }
        }

        //revision fechas entre ruedas
        if (rueda1[i][rueda1[0].size()-2] < 0 && rueda1[i][rueda1[0].size()-1] < 0 && rueda2[i][0] < 0){
            cantidad_conflictos++;
            if (is_in_vector(equipos_con_conflictos, i+1) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                equipos_con_conflictos.push_back(i+1);
            }
        }

        if (rueda1[i][rueda1[0].size()-1] < 0 && rueda2[i][0] < 0 && rueda2[i][1] < 0){
            cantidad_conflictos++;
            if (is_in_vector(equipos_con_conflictos, i+1) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                equipos_con_conflictos.push_back(i+1);
            }
        }

        //revisando segunda rueda

        for (int j = 0; j < rueda2[0].size()-2; j++){
            if (rueda2[i][j] < 0 && rueda2[i][j+1] < 0 && rueda2[i][j+2] < 0){
                cantidad_conflictos++;
                if (is_in_vector(equipos_con_conflictos, i+1) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                    equipos_con_conflictos.push_back(i+1);
                }
            }
        }
    }
    return cantidad_conflictos;
}

// las dos primeras y ultimas fechas no se pueden jugar ambas como visitante
// C12a y C12b
int revision_primeras_ultimas_fechas_visitante(vector<vector<int>> rueda1, vector<vector<int>> rueda2){
    int cantidad_conflictos = 0;
    int cant_fechas_rueda = rueda1[0].size();
    int cant_equipos = rueda1.size();
    vector<int> equipos_con_conflicto;

    for (int i = 0; i < cant_equipos; i++){
        if (rueda1[i][0] < 0 && rueda1[i][1] < 0){
            cantidad_conflictos++;
            if (is_in_vector(equipos_con_conflicto, i+1) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                equipos_con_conflicto.push_back(i+1);
            }
        }
        if (rueda2[i][cant_fechas_rueda-2] < 0 && rueda2[i][cant_fechas_rueda-1] < 0){
            cantidad_conflictos++;
            if (is_in_vector(equipos_con_conflicto, i+1) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                equipos_con_conflicto.push_back(i+1);
            }
        }
    
    }
    return cantidad_conflictos;
}

// las dos primeras y ultimas fechas no se pueden jugar ambas como local
// C12a y C12b
int revision_primeras_ultimas_fechas_local(vector<vector<int>> rueda1, vector<vector<int>> rueda2){
    int cantidad_conflictos = 0;
    int cant_fechas_rueda = rueda1[0].size();
    int cant_equipos = rueda1.size();
    vector<int> equipos_con_conflicto;

    for (int i = 0; i < cant_equipos; i++){
        if (rueda1[i][0] > 0 && rueda1[i][1] > 0){
            cantidad_conflictos++;
            if (is_in_vector(equipos_con_conflicto, i+1) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                equipos_con_conflicto.push_back(i+1);
            }
        }
        if (rueda2[i][cant_fechas_rueda-2] > 0 && rueda2[i][cant_fechas_rueda-1] > 0){
            cantidad_conflictos++;
            if (is_in_vector(equipos_con_conflicto, i+1) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                equipos_con_conflicto.push_back(i+1);
            }
        }
    
    }
    return cantidad_conflictos;
}

//Balance local visita entre un grupo de fechas Bank Holidays
//C106
int balance_bank_holidays(vector<vector<int>> rueda1, vector<vector<int>> rueda2, vector<int> fechas_bank_holidays){
    int cantidad_conflictos = 0;
    int cant_fechas_rueda = rueda1[0].size();
    int cant_equipos = rueda1.size();
    //int fechas_revisar_segunda_rueda;
    vector<int> equipos_con_conflicto;

    for (int i = 0; i < cant_equipos; i++){
        int contador_local = 0;
        int contador_visitante = 0;
        for (int j = 0; j < fechas_bank_holidays.size(); j++){
            if (fechas_bank_holidays[j] <= cant_fechas_rueda){ // fecha esta en la primera rueda
                if (rueda1[i][fechas_bank_holidays[j]-1] > 0){
                    contador_local++;
                }
                else{
                    contador_visitante++;
                }
            }
            else{ // fecha esta en la segunda rueda
                if (rueda2[i][fechas_bank_holidays[j]-1-cant_fechas_rueda] > 0){
                    contador_local++;
                }
                else{
                    contador_visitante++;
                }
            }
        }
        if (abs(contador_local - contador_visitante) > 1){
            cantidad_conflictos++;
            if (is_in_vector(equipos_con_conflicto, i+1) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                equipos_con_conflicto.push_back(i+1);
            }
        }
    }
    return cantidad_conflictos;
}

// fechas donde equipos fuertes no se deben enfrentar entre ellos
// C102a C102b
int enfrentamientos_entre_equipos_fuertes(vector<vector<int>> rueda1, vector<vector<int>> rueda2, vector<int> equipos_fuertes, int fecha_comparacion){
    int cantidad_conflictos = 0;
    int fecha_segunda_rueda;
    vector<int> equipos_con_conflictos;

    if (fecha_comparacion <= rueda1[0].size()){ // la fecha esta en la primera rueda
        //cout << "Fecha en primera rueda" << endl;
        for (int i = 0; i < equipos_fuertes.size(); i++){
            if (is_in_vector(equipos_fuertes, abs(rueda1[equipos_fuertes[i]-1][fecha_comparacion-1]))){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                equipos_con_conflictos.push_back(equipos_fuertes[i]);
                cantidad_conflictos++;
                if (is_in_vector(equipos_con_conflictos, equipos_fuertes[i]) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                    equipos_con_conflictos.push_back(equipos_fuertes[i]);
                }
            }
        }
    }
    else{ // la fecha esta en la segunda rueda
        //cout << "Fecha en segunda rueda" << endl;
        fecha_segunda_rueda = fecha_comparacion - rueda1[0].size();
        for (int i = 0; i < equipos_fuertes.size(); i++){
            if (is_in_vector(equipos_fuertes, abs(rueda2[equipos_fuertes[i]-1][fecha_segunda_rueda-1]))){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                equipos_con_conflictos.push_back(equipos_fuertes[i]);
                cantidad_conflictos++;
                if (is_in_vector(equipos_con_conflictos, equipos_fuertes[i]) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                    equipos_con_conflictos.push_back(equipos_fuertes[i]);
                }
            }
        }
    }
    return cantidad_conflictos;
}


// fechas donde equipos no deben jugar de local en ciertas fechas

//C04
//se asume que equipos y fechas tienen el mismo largo, en cada posicion se encuentra el equipo y la fecha que no debe jugar como local
int solicitud_no_jugar_como_local (vector<vector<int>> rueda1, vector<vector<int>> rueda2, vector<int> equipos, vector<int> fechas_solicitudes){
    int cantidad_conflictos = 0;
    int fecha_segunda_rueda;

    for (int i = 0; i < equipos.size(); i++){
        //cout << "Equipo " << equipos[i] << " no debe jugar como local en la fecha " << fechas_solicitudes[i] << endl;

        if (fechas_solicitudes[i] <= rueda1[0].size()){ // fecha esta en la primera rueda
            if (rueda1[equipos[i]-1][fechas_solicitudes[i]-1] > 0){
            cantidad_conflictos++;
        }
        }
        else{ // fecha esta en la segunda rueda
            //cout << "Fecha en segunda rueda: " << endl;
            fecha_segunda_rueda = fechas_solicitudes[i] - rueda1[0].size();
            //cout << "Fecha en segunda rueda: " << fecha_segunda_rueda << endl;
            if (rueda2[equipos[i]-1][fecha_segunda_rueda-1] > 0){
                cantidad_conflictos++;
            }
        }
    }
    //cout << "Cantidad de conflictos: " << cantidad_conflictos << endl;
    return cantidad_conflictos;
}

// Especificas PL

// equipos no pueden tener la misma condicion en boxing day y new year
// C12c
int distinta_condicion_boxingday_newyear(vector<vector<int>> rueda1, vector<vector<int>> rueda2, int fecha_boxing_day, int fecha_new_year){
    int cantidad_conflictos = 0;
    vector<int> equipos_con_conflictos;
    int rueda_boxing_day, rueda_new_year;

    if (fecha_boxing_day <= rueda1[0].size()){ // fecha esta en la primera rueda
        rueda_boxing_day = 1;
    }
    else{ // fecha esta en la segunda rueda
        rueda_boxing_day = 2;
        fecha_boxing_day = fecha_boxing_day - rueda1[0].size();
    }

    if (fecha_new_year <= rueda1[0].size()){ // fecha esta en la primera rueda
        rueda_new_year = 1;
    }
    else{ // fecha esta en la segunda rueda
        rueda_new_year = 2;
        fecha_new_year = fecha_new_year - rueda1[0].size();
    }

    for (int i = 0; i < rueda1.size(); i++){
        if (rueda_boxing_day == 1 && rueda_new_year == 1){
            if(rueda1[i][fecha_boxing_day-1] > 0 && rueda1[i][fecha_new_year-1] > 0 || rueda1[i][fecha_boxing_day-1] < 0 && rueda1[i][fecha_new_year-1] < 0){
                cantidad_conflictos++;
                equipos_con_conflictos.push_back(i+1);
            }
        }
        else if (rueda_boxing_day == 1 && rueda_new_year == 2){
            if(rueda1[i][fecha_boxing_day-1] > 0 && rueda2[i][fecha_new_year-1] > 0 || rueda1[i][fecha_boxing_day-1] < 0 && rueda2[i][fecha_new_year-1] < 0){
                cantidad_conflictos++;
                equipos_con_conflictos.push_back(i+1);
            }
        }
        else if (rueda_boxing_day == 2 && rueda_new_year == 2){
            if(rueda1[i][fecha_boxing_day-1] > 0 && rueda2[i][fecha_new_year-1] > 0 || rueda1[i][fecha_boxing_day-1] < 0 && rueda2[i][fecha_new_year-1] < 0){
                cantidad_conflictos++;
                equipos_con_conflictos.push_back(i+1);
            }
        }
            
    }
    return cantidad_conflictos;
}

// los dos partidos que se disputan antes y despues de FA cup no pueden ser ambos como visitante
// C105
int no_jugar_ambos_como_visitante(vector<vector<int>> rueda1, vector<vector<int>> rueda2, vector<int> fechas_previas, vector<int> fechas_posteriores){
    int cantidad_conflictos = 0;
    vector<int> equipos_con_conflictos;
    int ronda_fecha_previa, ronda_fecha_posterior, cantidad_visitante, fecha_previa_ronda_2, fecha_posterior_ronda_2;

    for (int i = 0; i < rueda1.size(); i++){ // recorriendo por equipo

        for (int j=0; j < fechas_previas.size(); j++){
            
            cantidad_visitante = 0;

            if (fechas_previas[j] <= rueda1[0].size()){ // fecha esta en la primera rueda
                ronda_fecha_previa = 1;
            }
            else{ // fecha esta en la segunda rueda
                ronda_fecha_previa = 2;
                fecha_previa_ronda_2 = fechas_previas[j] - rueda1[0].size();
            }

            if (fechas_posteriores[j] <= rueda1[0].size()){ // fecha esta en la primera rueda
                ronda_fecha_posterior = 1;
            }
            else{ // fecha esta en la segunda rueda
                ronda_fecha_posterior = 2;
                fecha_posterior_ronda_2 = fechas_posteriores[j] - rueda1[0].size();
            }

            if (ronda_fecha_previa == 1 && ronda_fecha_posterior == 1){
                if (rueda1[i][fechas_previas[j]-1] < 0){
                    cantidad_visitante++;
                }
                if (rueda1[i][fechas_posteriores[j]-1] < 0){
                    cantidad_visitante++;
                }
            }
            else if (ronda_fecha_previa == 1 && ronda_fecha_posterior == 2){
                if (rueda1[i][fechas_previas[j]-1] < 0){
                    cantidad_visitante++;
                }
                if (rueda2[i][fecha_posterior_ronda_2-1] < 0){
                    cantidad_visitante++;
                }
            }
            else if (ronda_fecha_previa == 2 && ronda_fecha_posterior == 2){
                if (rueda2[i][fecha_previa_ronda_2-1] < 0){
                    cantidad_visitante++;
                }
                if (rueda2[i][fecha_posterior_ronda_2-1] < 0){
                    cantidad_visitante++;
                }
            }

            if (cantidad_visitante == 2){
                cantidad_conflictos++;
                //cout << "Hay conflicto en la fechas " << fechas_previas[j] << " y " << fechas_posteriores[j] << " para el equipo " << i+1 << endl;

                if (is_in_vector(equipos_con_conflictos, i+1) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                    equipos_con_conflictos.push_back(i+1);
                }
            }
        }
    }

    return cantidad_conflictos;
}

// no se puede tener el mismo rival en boxing day y año nuevo
// C108
int rival_boxing_day_new_year_diferente(vector<vector<int>> rueda1, vector<vector<int>> rueda2, int fecha_boxing_day, int fecha_new_year){
    int cantidad_conflictos = 0;
    vector<int> equipos_con_conflictos;
    int rueda_boxing_day, rueda_new_year;

    if (fecha_boxing_day <= rueda1[0].size()){ // fecha esta en la primera rueda
        rueda_boxing_day = 1;
    }
    else{ // fecha esta en la segunda rueda
        rueda_boxing_day = 2;
        fecha_boxing_day = fecha_boxing_day - rueda1[0].size();
    }

    if (fecha_new_year <= rueda1[0].size()){ // fecha esta en la primera rueda
        rueda_new_year = 1;
    }
    else{ // fecha esta en la segunda rueda
        rueda_new_year = 2;
        fecha_new_year = fecha_new_year - rueda1[0].size();
    }

    for (int i = 0; i < rueda1.size(); i++){
        if (rueda_boxing_day == 1 && rueda_new_year == 1){
            if(abs(rueda1[i][fecha_boxing_day-1]) == abs(rueda1[i][fecha_new_year-1])){
                cantidad_conflictos++;
                if (is_in_vector(equipos_con_conflictos, i+1) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                    equipos_con_conflictos.push_back(i+1);
                }
            }
        }
        else if (rueda_boxing_day == 1 && rueda_new_year == 2){
            if(abs(rueda1[i][fecha_boxing_day-1]) == abs(rueda2[i][fecha_new_year-1])){
                cantidad_conflictos++;
                if (is_in_vector(equipos_con_conflictos, i+1) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                    equipos_con_conflictos.push_back(i+1);
                }
            }
        }
        else if (rueda_boxing_day == 2 && rueda_new_year == 2){
            if(abs(rueda2[i][fecha_boxing_day-1]) == abs(rueda2[i][fecha_new_year-1])){
                cantidad_conflictos++;
                if (is_in_vector(equipos_con_conflictos, i+1) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                    equipos_con_conflictos.push_back(i+1);
                }
            }
        }
    } 
    return cantidad_conflictos;
}

// equipos emparejados no deben jugar como locales en la misma fecha
// C07
// Ojo que en este caso se contabiliza dos veces, ya que t1 esta emparejado con t2 y t2 con t1
int evitar_localias_equipos_emparejados(vector<vector<int>> rueda1, vector<vector<int>> rueda2, vector<int> equipos_emparejados){
    int cantidad_conflictos = 0;
    int equipo_emparejado;
    vector<int> equipos_con_conflictos;

    for (int i = 0; i < rueda1.size(); i++){ // recorriendo los equipos
        if (equipos_emparejados[i] > 0){ // si el equipo tiene un rival emparejado
            equipo_emparejado = equipos_emparejados[i];
            // en cada fecha se debe revisar que el equipo actual y su rival no jueguen ambos como local

            //revisando primera rueda
            for (int j = 0; j < rueda1[0].size(); j++){
                if (rueda1[i][j] > 0 && rueda1[equipo_emparejado-1][j] > 0){

                    //cout << "Equipo " << i+1 << " y " << equipo_emparejado << " estan emparejados en la fecha " << j+1 << endl;

                    cantidad_conflictos++;
                    if (is_in_vector(equipos_con_conflictos, i+1) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                        equipos_con_conflictos.push_back(i+1);
                    }
                }
            }

            //revisando segunda rueda
            for (int j = 0; j < rueda2[0].size(); j++){
                if (rueda2[i][j] > 0 && rueda2[equipo_emparejado-1][j] > 0){
                    cantidad_conflictos++;
                    if (is_in_vector(equipos_con_conflictos, i+1) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                        equipos_con_conflictos.push_back(i+1);
                    }
                }
            }

        }
    }

    return cantidad_conflictos;
}

//equipos emparejados no deben enfrentarse en boxing day y año nuevo
// C103
int evitar_fechas_festivas_equipos_emparejados(vector<vector<int>> rueda1, vector<vector<int>> rueda2, vector<int> equipos_emparejados, int boxing_day, int new_year){
    int cantidad_conflictos = 0;
    int rueda_boxing_day, rueda_new_year;

    if (boxing_day <= rueda1[0].size()){ // fecha esta en la primera rueda
        rueda_boxing_day = 1;
    }
    else{ // fecha esta en la segunda rueda
        rueda_boxing_day = 2;
        boxing_day = boxing_day - rueda1[0].size();
    }

    if (new_year <= rueda1[0].size()){ // fecha esta en la primera rueda
        rueda_new_year = 1;
    }
    else{ // fecha esta en la segunda rueda
        rueda_new_year = 2;
        new_year = new_year - rueda1[0].size();
    }
    
    for (int i = 0; i < rueda1.size(); i++){ // recorriendo los equipos
        if (equipos_emparejados[i] > 0){ // si el equipo tiene un rival emparejado

            if (rueda_boxing_day == 1){
                if (abs(rueda1[i][boxing_day-1]) == equipos_emparejados[i]){
                    cantidad_conflictos++;
                }
            }
            else{
                if (abs(rueda2[i][boxing_day-1]) == equipos_emparejados[i]){
                    cantidad_conflictos++;
                }
            }

            if (rueda_new_year == 1){
                if (abs(rueda1[i][new_year-1]) == equipos_emparejados[i]){
                    cantidad_conflictos++;
                }
            }
            else{
                if (abs(rueda2[i][new_year-1]) == equipos_emparejados[i]){
                    cantidad_conflictos++;
                }
            }

        }
    }
    return cantidad_conflictos;
}

// calcular distancias boxing day y año nuevo
// C107
float distancia_festivos(vector<vector<int>> rueda1, vector<vector<int>> rueda2, vector<vector<int>> distancias, int fecha_boxing_day, int fecha_new_year){
    
    float distancia = 0;
    int rueda_boxing_day, rueda_new_year, rival;

    if (fecha_boxing_day <= rueda1[0].size()){ // fecha esta en la primera rueda
        rueda_boxing_day = 1;
    }
    else{ // fecha esta en la segunda rueda
        rueda_boxing_day = 2;
        fecha_boxing_day = fecha_boxing_day - rueda1[0].size();
    }

    if (fecha_new_year <= rueda1[0].size()){ // fecha esta en la primera rueda
        rueda_new_year = 1;
    }
    else{ // fecha esta en la segunda rueda
        rueda_new_year = 2;
        fecha_new_year = fecha_new_year - rueda1[0].size();
    }

    for (int i = 0; i < rueda1.size(); i++){

        // revisando boxing day

        if (rueda_boxing_day == 1){
            if(rueda1[i][fecha_boxing_day-1] < 0){ // el equipo debe trasladarse donde su rival
                rival = abs(rueda1[i][fecha_boxing_day-1]);
                distancia += distancias[i][rival-1];
                if (distancias[i][rival-1] > 1000){
                    //cout << "Equipo " << i+1 << " y " << rival << " estan emparejados en boxing day" << endl;
                }
            }
        }
        else{
            if(rueda2[i][fecha_boxing_day-1] < 0){ // el equipo debe trasladarse donde su rival
                rival = abs(rueda2[i][fecha_boxing_day-1]);
                distancia += distancias[i][rival-1];
                if (distancias[i][rival-1] > 1000){
                    //cout << "Equipo " << i+1 << " y " << rival << " estan emparejados en boxing day" << endl;
                }
            }
        }

        // revisando año nuevo

        if (rueda_new_year == 1){
            if(rueda1[i][fecha_new_year-1] < 0){ // el equipo debe trasladarse donde su rival
                rival = abs(rueda1[i][fecha_new_year-1]);
                distancia += distancias[i][rival-1];
                if (distancias[i][rival-1] > 1000){
                    //cout << "Equipo " << i+1 << " y " << rival << " estan emparejados en año nuevo" << endl;
                }
            }
        }
        else{
            if(rueda2[i][fecha_new_year-1] < 0){ // el equipo debe trasladarse donde su rival
                rival = abs(rueda2[i][fecha_new_year-1]);
                distancia += distancias[i][rival-1];
                if (distancias[i][rival-1] > 1000){
                    //cout << "Equipo " << i+1 << " y " << rival << " estan emparejados en año nuevo" << endl;
                }
            }
        }
    }
    
    return distancia;
}


// ESPECIFICAS CHILE

//retorna la cantidad de equipos que tienen un desbalance entre local y vista hasta la fecha de comparacion (incluyendola)
int balance_local_visitante(vector<vector<int>> rueda1, vector<vector<int>> rueda2, int fecha_comparacion){
    int cantidad__equipos_con_conflictos = 0;
    int cant_fechas_rueda = rueda1[0].size();
    int cant_equipos = rueda1.size();
    int fechas_revisar_segunda_rueda;
    vector<int> equipos_con_conflicto;

    if(fecha_comparacion <= cant_fechas_rueda){ // solo se revisa la primera rueda
        //cout << "Solo se revisa la primera rueda" << endl;
        //cout << "Fecha de comparacion: " << fecha_comparacion << " esta en la primera rueda" << endl;
        for(int i = 0; i < cant_equipos; i++){
            int contador_local = 0;
            int contador_visitante = 0;
            for(int j = 0; j < fecha_comparacion; j++){
                if (rueda1[i][j] > 0){
                    contador_local++;
                } else {
                    contador_visitante++;
                }
            }
            if (abs(contador_local - contador_visitante) > 1){
                cantidad__equipos_con_conflictos++;
                equipos_con_conflicto.push_back(i+1);
                //cout << "Equipo con desbalance: " << i+1 << " con la bank holiday " << fecha_comparacion << endl;

            }
        }
    }
    else{ // hay que revisar ambas ruedas
        //cout << "Se revisan ambas ruedas" << endl;
        //cout << "Fecha de comparacion: " << fecha_comparacion << " esta en la segunda rueda" << endl;
        fechas_revisar_segunda_rueda = fecha_comparacion - cant_fechas_rueda;
        for(int i = 0; i < cant_equipos; i++){
            int contador_local = 0;
            int contador_visitante = 0;

            for(int j = 0; j < cant_fechas_rueda; j++){ // revisa la primera rueda
                if (rueda1[i][j] > 0){
                    contador_local++;
                } else {
                    contador_visitante++;
                }
            }

            for(int j = 0; j < fechas_revisar_segunda_rueda; j++){ // revisa la segunda rueda
                if (rueda2[i][j] > 0){
                    contador_local++;
                } else {
                    contador_visitante++;
                }
            }
            if (abs(contador_local - contador_visitante) > 1){
                cantidad__equipos_con_conflictos++;
                //cout << "Equipo con desbalance: " << i+1 << " con la bank holiday " << fecha_comparacion << endl;
                equipos_con_conflicto.push_back(i+1);
            }
        }
    }

    return cantidad__equipos_con_conflictos;
}

// hay algunas restricciones de las anteriores que se van a reutilizar

// restriccion equipos por zona (norte, centro, sur)

// equipos del norte no pueden jugar dos partidos seguidos como visitante en el sur
// equipos del sur no pueden jugar dos partidos seguidos como visitante en el norte
// equipos de la zona centro al jugar dos partidos consecutivos como visitante, al menos uno debe ser en la zona centro

int revision_equipos_zona(vector<vector<int>> rueda1, vector<vector<int>> rueda2, vector<int> equipos_norte, vector<int> equipos_centro, vector<int> equipos_sur){
    int cantidad_conflictos = 0;
    vector<int> equipos_con_conflictos;
    int rival;
    int rueda_fecha;
    int equipo_revision,rival_1, rival_2;

    //revisando equipos norte
    for(int i = 0; i < equipos_norte.size(); i++){
        equipo_revision = equipos_norte[i];
        // si el equipo i disputa dos fechas seguidas como visitante hay que revisar si esos dos equipos no son del sur

        //revisando primera rueda
        for (int j = 0; j < rueda1[0].size(); j++){
            if (rueda1[equipo_revision-1][j] < 0 && rueda1[equipo_revision-1][j+1] < 0){ // juega dos partidos de visitante seguidos
                rival_1 = abs(rueda1[equipo_revision-1][j]);
                rival_2 = abs(rueda1[equipo_revision-1][j+1]);
                if (is_in_vector(equipos_sur, rival_1) == true && is_in_vector(equipos_sur, rival_2) == true){ // los dos equipos son del sur
                    cantidad_conflictos++;
                    if (is_in_vector(equipos_con_conflictos, equipos_norte[i]) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                        equipos_con_conflictos.push_back(equipos_norte[i]);
                    }
                }
                
            }
        }

        // revisando fecha entre ruedas
        if (rueda1[equipo_revision-1][rueda1[0].size()-1] < 0 && rueda2[equipo_revision-1][0] < 0){ // juega dos partidos de visitante seguidos
            rival_1 = abs(rueda1[equipo_revision-1][rueda1[0].size()-1]);
            rival_2 = abs(rueda1[equipo_revision-1][0]);
            if (is_in_vector(equipos_sur, rival_1) == true && is_in_vector(equipos_sur, rival_2) == true){ // los dos equipos son del sur
                cantidad_conflictos++;
                if (is_in_vector(equipos_con_conflictos, equipos_norte[i]) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                    equipos_con_conflictos.push_back(equipos_norte[i]);
                }
            }
                
        }

        //revisando segunda rueda
        for (int j = 0; j < rueda2[0].size()-1; j++){
            if (rueda2[equipo_revision-1][j] < 0 && rueda2[equipo_revision-1][j+1] < 0){ // juega dos partidos de visitante seguidos
                rival_1 = abs(rueda2[equipo_revision-1][j]);
                rival_2 = abs(rueda2[equipo_revision-1][j+1]);
                if (is_in_vector(equipos_sur, rival_1) == true && is_in_vector(equipos_sur, rival_2) == true){ // los dos equipos son del sur
                    cantidad_conflictos++;
                    if (is_in_vector(equipos_con_conflictos, equipos_norte[i]) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                        equipos_con_conflictos.push_back(equipos_norte[i]);
                    }
                }
                
            }
        }
    }

    //revisando equipos centro
    for(int i = 0; i < equipos_centro.size(); i++){
        equipo_revision = equipos_centro[i];

        //revisando primera rueda
        for (int j = 0; j < rueda1[0].size()-1; j++){
            if (rueda1[equipo_revision-1][j] < 0 && rueda1[equipo_revision-1][j+1] < 0){ // juega dos partidos de visitante seguidos
                rival_1 = abs(rueda1[equipo_revision-1][j]);
                rival_2 = abs(rueda1[equipo_revision-1][j+1]);
                if (!(is_in_vector(equipos_centro, rival_1) == true || is_in_vector(equipos_centro, rival_2) == true)){ // si ninguno de los dos equipos es del centro
                    cantidad_conflictos++;
                    if (is_in_vector(equipos_con_conflictos, equipos_centro[i]) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                        equipos_con_conflictos.push_back(equipos_centro[i]);
                    }
                }
            }
        }    

        // revisando fecha entre ruedas
        if (rueda1[equipo_revision-1][rueda1[0].size()-1] < 0 && rueda2[equipo_revision-1][0] < 0){ // juega dos partidos de visitante seguidos
            rival_1 = abs(rueda1[equipo_revision-1][rueda1[0].size()-1]);
            rival_2 = abs(rueda2[equipo_revision-1][0]);
            if (!(is_in_vector(equipos_centro, rival_1) == true || is_in_vector(equipos_centro, rival_2) == true)){ // si ninguno de los dos equipos es del centro
                cantidad_conflictos++;
                if (is_in_vector(equipos_con_conflictos, equipos_centro[i]) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                    equipos_con_conflictos.push_back(equipos_centro[i]);
                }
            }
        }

        //revisando segunda rueda
        for (int j = 0; j < rueda1[0].size()-1; j++){
            if (rueda2[equipo_revision-1][j] < 0 && rueda2[equipo_revision-1][j+1] < 0){ // juega dos partidos de visitante seguidos
                rival_1 = abs(rueda2[equipo_revision-1][j]);
                rival_2 = abs(rueda2[equipo_revision-1][j+1]);
                if (!(is_in_vector(equipos_centro, rival_1) == true || is_in_vector(equipos_centro, rival_2) == true)){ // si ninguno de los dos equipos es del centro
                    cantidad_conflictos++;
                    if (is_in_vector(equipos_con_conflictos, equipos_centro[i]) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                        equipos_con_conflictos.push_back(equipos_centro[i]);
                    }
                }
            }
        }   
    }

    //revisando equipos sur
    for(int i = 0; i < equipos_sur.size(); i++){
        equipo_revision = equipos_sur[i];
        // si el equipo i disputa dos fechas seguidas como visitante hay que revisar si esos dos equipos no son del sur

        //revisando primera rueda
        for (int j = 0; j < rueda1[0].size()-1; j++){
            if (rueda1[equipo_revision-1][j] < 0 && rueda1[equipo_revision-1][j+1] < 0){ // juega dos partidos de visitante seguidos
                rival_1 = abs(rueda1[equipo_revision-1][j]);
                rival_2 = abs(rueda1[equipo_revision-1][j+1]);
                if (is_in_vector(equipos_norte, rival_1) == true && is_in_vector(equipos_norte, rival_2) == true){ // los dos equipos son del norte
                    cantidad_conflictos++;
                    if (is_in_vector(equipos_con_conflictos, equipos_sur[i]) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                        equipos_con_conflictos.push_back(equipos_sur[i]);
                    }
                }
                
            }
        }    

        // revisando fecha entre ruedas
        if (rueda1[equipo_revision-1][rueda1[0].size()-1] < 0 && rueda2[equipo_revision-1][0] < 0){ // juega dos partidos de visitante seguidos
            rival_1 = abs(rueda1[equipo_revision-1][rueda1[0].size()-1]);
            rival_2 = abs(rueda1[equipo_revision-1][0]);
            if (is_in_vector(equipos_norte, rival_1) == true && is_in_vector(equipos_norte, rival_2) == true){ // los dos equipos son del sur
                cantidad_conflictos++;
                if (is_in_vector(equipos_con_conflictos, equipos_sur[i]) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                    equipos_con_conflictos.push_back(equipos_sur[i]);
                }
            }
                
        }

        //revisando segunda rueda
        for (int j = 0; j < rueda2[0].size()-1; j++){
            if (rueda2[equipo_revision-1][j] < 0 && rueda2[equipo_revision-1][j+1] < 0){ // juega dos partidos de visitante seguidos
                rival_1 = abs(rueda2[equipo_revision-1][j]);
                rival_2 = abs(rueda2[equipo_revision-1][j+1]);
                if (is_in_vector(equipos_norte, rival_1) == true && is_in_vector(equipos_norte, rival_2) == true){ // los dos equipos son del norte
                    cantidad_conflictos++;
                    if (is_in_vector(equipos_con_conflictos, equipos_sur[i]) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                        equipos_con_conflictos.push_back(equipos_sur[i]);
                    }
                }
                
            }
        }    
    }
    return cantidad_conflictos;
}


// evitar clasicos (enfrentemientos entre equipos fuertes) en las primeras 3 y ultimas 3 fechas
int enfrentamientos_entre_equipos_fuertes(vector<vector<int>> rueda1, vector<vector<int>> rueda2, vector<int> equipos_fuertes, vector<int> fechas_enfrentamientos){
    int cantidad_conflictos = 0;
    vector<int> equipos_con_conflictos;
    int rueda_fecha, rival;
    int fecha_en_rueda;

    for (int i = 0; i < equipos_fuertes.size(); i++){
        for (int j = 0; j < fechas_enfrentamientos.size(); j++){
            if (fechas_enfrentamientos[j] <= rueda1[0].size()){ // fecha esta en la primera rueda
                rueda_fecha = 1;
                fecha_en_rueda = fechas_enfrentamientos[j];
            }
            else{ // fecha esta en la segunda rueda
                rueda_fecha = 2;
                fecha_en_rueda = fechas_enfrentamientos[j] - rueda1[0].size();
            }

            if (rueda_fecha == 1){
                rival = abs(rueda1[equipos_fuertes[i]-1][fecha_en_rueda-1]);
            }
            else{
                rival = abs(rueda2[equipos_fuertes[i]-1][fecha_en_rueda-1]);
            }

            if (is_in_vector(equipos_fuertes, rival) == true){
                cantidad_conflictos++;
                if (is_in_vector(equipos_con_conflictos, equipos_fuertes[i]) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                    equipos_con_conflictos.push_back(equipos_fuertes[i]);
                }
            }
        }
    }
    return cantidad_conflictos;
}

// cada equipo fuerte debe jugar un clasico como local y uno como visita ESPECIFICA PARA FURBOL CHILENO
//basta con revisar una rueda, ya que si se cumple en la primera rueda se cumple en la segunda y viceversa
int clasicos_local_visitante(vector<vector<int>> rueda1, vector<vector<int>> rueda2, vector<int> equipos_fuertes){
    int cantidad_conflictos = 0;
    vector<int> equipos_con_conflictos;
    int rival;
    int rueda_fecha, contador_local, contador_visitante;

    
    for (int i = 0; i < equipos_fuertes.size(); i++){
        int equipo_revision = equipos_fuertes[i];
        contador_local = 0;
        contador_visitante = 0;
        //revision primera rueda
        for (int j = 0; j < rueda1[0].size(); j++){
            if (is_in_vector(equipos_fuertes,abs(rueda1[equipo_revision-1][j]))){ // si el rival es un equipo fuerte
                if (rueda1[equipo_revision-1][j] > 0){
                    contador_local++;
                }
                else{
                    contador_visitante++;
                }
            }
        }

        if (contador_local != contador_visitante){ // no se juega un clasico como local y uno como visita en esa rueda
            cantidad_conflictos++;
            if (is_in_vector(equipos_con_conflictos, equipos_fuertes[i]) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                equipos_con_conflictos.push_back(equipos_fuertes[i]);
            }
        }

    }
    return cantidad_conflictos;
}

//fechas consecutivas contra equipos fuertes
int fechas_consecutivas_equipos_fuertes(vector<vector<int>> rueda1, vector<vector<int>> rueda2, vector<int> equipos_fuertes){
    int rival_1,rival_2;
    int cantidad_conflictos = 0;
    vector<int> equipos_con_conflictos;

    for(int i = 0; i < rueda1.size(); i++){
        //revisando primera rueda
        for (int j = 0; j < rueda1[0].size()-1; j++){
            if (rueda1[i][j] < 0 && rueda1[i][j+1] < 0){ // juega dos partidos de visitante seguidos
                rival_1 = abs(rueda1[i][j]);
                rival_2 = abs(rueda1[i][j+1]);
                if (is_in_vector(equipos_fuertes, rival_1) == true && is_in_vector(equipos_fuertes, rival_2) == true){ // los dos equipos son rivales fuertes
                    cantidad_conflictos++;
                    if (is_in_vector(equipos_con_conflictos, i+1) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                        equipos_con_conflictos.push_back(i+1);
                    }
                }
            }
        }

        // revisando fecha entre ruedas
        if (rueda1[i][rueda1[0].size()-1] < 0 && rueda2[i][0] < 0){ // juega dos partidos de visitante seguidos
            rival_1 = abs(rueda1[i][rueda1[0].size()-1]);
            rival_2 = abs(rueda1[i][0]);
            if (is_in_vector(equipos_fuertes, rival_1) == true && is_in_vector(equipos_fuertes, rival_2) == true){ // los dos equipos son del sur
                cantidad_conflictos++;
                if (is_in_vector(equipos_con_conflictos, i+1) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                    equipos_con_conflictos.push_back(i+1);
                }
            }
        }

        //revisando segunda rueda
        for (int j = 0; j < rueda2[0].size()-1; j++){
            if (rueda2[i][j] < 0 && rueda2[i][j+1] < 0){ // juega dos partidos de visitante seguidos
                rival_1 = abs(rueda2[i][j]);
                rival_2 = abs(rueda2[i][j+1]);
                if (is_in_vector(equipos_fuertes, rival_1) == true && is_in_vector(equipos_fuertes, rival_2) == true){ // los dos equipos son del sur
                    cantidad_conflictos++;
                    if (is_in_vector(equipos_con_conflictos, i+1) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                        equipos_con_conflictos.push_back(i+1);
                    }
                }
            }
        }
    }
    return cantidad_conflictos; // veces que un equipo se enfrenta a dos equipos fuertes de forma consecutiva
}

// equipos en zonas de vacaciones
int equipos_zonas_vacaciones(vector<vector<int>> rueda1, vector<int> equipos_vacaciones,vector<int> equipos_fuertes, int fecha_limite_vacaciones){
    int cantidad_conflictos = 0;
    vector<int> equipos_con_conflictos;
    bool cumple_restriccion;

    // los equipos en zonas de vacaciones deben jugar como local contra un equipo fuerte antes de la fecha limite de vacaciones

    for (int i = 0; i < equipos_vacaciones.size(); i++){
        cumple_restriccion = false;
        for (int j = 0; j < fecha_limite_vacaciones-1; j++){
            if (rueda1[equipos_vacaciones[i]-1][j] < 0 && is_in_vector(equipos_fuertes, abs(rueda1[equipos_vacaciones[i]-1][j]))){
                cumple_restriccion = true;
            }
        }
        if (cumple_restriccion == false){
            cantidad_conflictos++;
            if (is_in_vector(equipos_con_conflictos, equipos_vacaciones[i]) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                equipos_con_conflictos.push_back(equipos_vacaciones[i]);
            }
        }
    }
    return cantidad_conflictos;
}

//veces que se rompe el patron de local/visitante
int contador_breaks(vector<vector<int>> rueda1, vector<vector<int>> rueda2){
    int cantidad_breaks = 0;
    int cant_fechas_rueda = rueda1[0].size();
    int cant_equipos = rueda1.size();
    vector<int> equipos_con_breakes;
    
    //revision primera rueda
    for (int i = 0; i < cant_equipos; i++){
        for (int j = 0; j < cant_fechas_rueda-1; j++){
            if (rueda1[i][j] < 0 && rueda1[i][j+1] < 0 && rueda1[i][j] > 0 && rueda1[i][j+1] > 0){
                cantidad_breaks++;
                if (is_in_vector(equipos_con_breakes, i+1) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                        equipos_con_breakes.push_back(i+1);
                }
            }
        }
        //revision ultima fecha con primera de la siguiente rueda
        if (rueda1[i][cant_fechas_rueda-1] < 0 && rueda2[i][0] < 0 && rueda1[i][cant_fechas_rueda-1] > 0 && rueda2[i][0] > 0){
            cantidad_breaks++;
            if (is_in_vector(equipos_con_breakes, i+1) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                    equipos_con_breakes.push_back(i+1);
            }
        }
    }

    //revision segunda rueda
    for (int i = 0; i < cant_equipos; i++){
        for (int j = 0; j < cant_fechas_rueda-1; j++){
            if (rueda2[i][j] < 0 && rueda2[i][j+1] < 0 && rueda2[i][j] > 0 && rueda2[i][j+1] > 0){
                cantidad_breaks++;
                if (is_in_vector(equipos_con_breakes, i+1) == false){ // si el equipo ya esta en la lista de los conflictos no lo agrega
                    equipos_con_breakes.push_back(i+1);
                }
            }
        }
    } 

    return cantidad_breaks;    
}

// restriccion para limitar que ciertos equipos juegen de local en simultaneo (Caso Santiago En PDC)

int equipos_local_simultaneo(vector<vector<int>> rueda1, vector<vector<int>> rueda2, vector<int> equipos_simultaneo, int min_simultaneo, int max_simultaneo){
    int cantidad_conflictos = 0;
    int contador_localias;
    vector<int> equipos_con_conflictos;

    // se debe revisar fecha por fecha los equipos sleccionados y ver si juegan como local o no

    for (int i = 0; i < rueda1[0].size(); i++){ // recoorre las fechas de la primera rueda
        contador_localias = 0;
        for (int j = 0; j < equipos_simultaneo.size(); j++){
            if (rueda1[equipos_simultaneo[j]-1][i] > 0){
                contador_localias++;
            }
        }
        if (contador_localias > max_simultaneo || contador_localias < min_simultaneo){
            cantidad_conflictos++;
        }
    }

    for (int i = 0; i < rueda2[0].size(); i++){ // recoorre las fechas de la segunda rueda
        contador_localias = 0;
        for (int j = 0; j < equipos_simultaneo.size(); j++){
            if (rueda2[equipos_simultaneo[j]-1][i] > 0){
                contador_localias++;
            }
        }
        if (contador_localias > max_simultaneo || contador_localias < min_simultaneo){
            cantidad_conflictos++;
            
        }
    }

    return cantidad_conflictos;
}

// restriccion de balance de loclias por reueda
//se revisa solo una rueda ya que si no se cumple en una, tampoco en la otra
int balance_localias_rueda(vector<vector<int>> rueda){

    //cout << "Revisando balance de localias" << endl;

    //out << "Cantidad de equipos: " << rueda.size() << endl;
    //cout << "Cantidad de fechas: " << rueda[0].size() << endl;

    int cantidad_conflictos = 0;
    for(int i = 0; i<rueda.size(); i++){

        //cout << "Revisando equipo " << i+1 << endl;

        int contador_local = 0;
        int contador_visitante = 0;
        for(int j = 0; j < 15; j++){
            if (rueda[i][j] > 0){
                contador_local++;
            } else {
                contador_visitante++;
            }
        }
        if (abs(contador_local - contador_visitante) > 1){
            cantidad_conflictos++;
        }
    }
    return cantidad_conflictos;
}