#include <iostream>
#include <vector>
#include "restricciones.cpp"
#include <iterator>
using namespace std;

int funcion_evaluacion_epl(int distiancia_optima, int fecha_boxing_day, int fecha_new_year, vector<vector<int>> rueda1, vector<vector<int>> rueda2, vector<int> equipos_fuertes, vector<int> equipos_UCL, vector<int> equipos_UEL,
    vector<int> equipos_UECL, vector<int> equipos_emparejados, vector <int >fechas_previas_FA_Cup, vector<int> fechas_posteriores_FA_Cup, vector<int> fechas_previas_UCL,
    vector<int> fechas_posteriores_UCL, vector<int> fechas_previas_UEL, vector<int> fechas_posteriores_UEL, vector<int> fechas_previas_UECL, vector<int> fechas_posteriores_UECL, vector<int> fechas_bank_holidays, 
    vector<vector<int>> solicituedes_visitante, vector<vector<int>> distancias){

    int evaluacion = 0;

    int peso_solicitudes_no_jugar_como_local = 60; //CO4
    int peso_equipos_emparejados_locales = 100; //C07
    int peso_equipos_fuertes_primera_fecha = 80; //C102a
    int peso_equipos_fuertes_fechas_festivas = 90; //C102b
    int peso_equipos_fuertes_previa_UCL = 45; //C102c
    int peso_equipos_fuertes_posterior_UCL = 30; //C102e
    int peso_equipos_fuertes_previa_UEL = 5; //C102d
    int peso_equipos_fuertes_posterior_UEL = 9; //C102f
    int peso_equipos_emparejados_fechas_festivas = 100; //C103
    int peso_break_primeras_ultimas_fechas = 90; //C12a y C12b
    int peso_condicion_diferente_fechas_festivas = 1000; //C12c
    int peso_maximo_3partidos_local_visitante = 100; //C13 y C14
    int peso_jugar_visitante_FACup = 2; //C105
    int peso_balance_bank_holidays = 50; //C106 
    float peso_distancias = 0.5; //C107
    int peso_equipos_diferentes_fechas_festivas = 1000; //C108
    int peso_cant_fechas_rival_nuevamente = 60; //C19
    
    //revision C04 solicitudes visitante
    vector<int> aux_equipos_solicitud_visitante;
    vector<int> aux_fechas_solicitud_visitante;
    for (int i = 0; i < solicituedes_visitante.size(); i++){
        aux_equipos_solicitud_visitante.push_back(solicituedes_visitante[i][0]);
        aux_fechas_solicitud_visitante.push_back(solicituedes_visitante[i][1]);
    }

    //cout << "Evaluacion de las restricciones: ------------------------------------------------------------------------------------------------" << endl;

    // revision C04 (60): Solicitudes no jugar como local
    evaluacion += solicitud_no_jugar_como_local(rueda1, rueda2, aux_equipos_solicitud_visitante, aux_fechas_solicitud_visitante)*peso_solicitudes_no_jugar_como_local;

    // revision C07 (100): Equipos emparejados no deben jugar como local en la misma fecha
    evaluacion += evitar_localias_equipos_emparejados(rueda1, rueda2, equipos_emparejados)*peso_equipos_emparejados_locales/2;

    // revision C102a (80): Equipos fuertes no deben enfrentarse en la primera fecha del torneo
    evaluacion += enfrentamientos_entre_equipos_fuertes(rueda1, rueda2, equipos_fuertes, 1)*peso_equipos_fuertes_primera_fecha/2;

    // revision C102b (80): Equipos fuertes no deben enfrentarse en boxing day y new year
    evaluacion += enfrentamientos_entre_equipos_fuertes(rueda1, rueda2, equipos_fuertes, fecha_boxing_day)*peso_equipos_fuertes_fechas_festivas/2;
    evaluacion += enfrentamientos_entre_equipos_fuertes(rueda1, rueda2, equipos_fuertes, fecha_new_year)*peso_equipos_fuertes_fechas_festivas/2;

    // revision C102c (45): Equipos no deben jugar contra un rival fuerte la fecha previa a la UCL
    evaluacion += equipo_fuerte_fecha_internacional(rueda1, rueda2, equipos_fuertes, equipos_UCL, fechas_previas_UCL)*peso_equipos_fuertes_previa_UCL;
    //cout << "(C102c) Equipos fuertes previa UCL: " << equipo_fuerte_fecha_internacional(rueda1, rueda2, equipos_fuertes, equipos_UCL, fechas_previas_UCL)*peso_equipos_fuertes_previa_UCL << endl;
    
    // revision C102d (5): Equipos no deben jugar contra un rival fuerte la fecha previa a la UEL
    evaluacion += equipo_fuerte_fecha_internacional(rueda1, rueda2, equipos_fuertes, equipos_UEL, fechas_previas_UEL)*peso_equipos_fuertes_previa_UEL;
    //cout << "(C102d) Equipos fuertes previa UEL: " << equipo_fuerte_fecha_internacional(rueda1, rueda2, equipos_fuertes, equipos_UEL, fechas_previas_UEL)*peso_equipos_fuertes_previa_UEL << endl;

    // revision C102e (30): Equipos no deben jugar contra un rival fuerte la fecha posterior a la UCL
    evaluacion += equipo_fuerte_fecha_internacional(rueda1, rueda2, equipos_fuertes, equipos_UCL, fechas_posteriores_UCL)*peso_equipos_fuertes_posterior_UCL;
    //cout << "(C102e) Equipos fuertes posterior UCL: " << equipo_fuerte_fecha_internacional(rueda1, rueda2, equipos_fuertes, equipos_UCL, fechas_posteriores_UCL)*peso_equipos_fuertes_posterior_UCL << endl;

    // revision C102f (9): Equipos no deben jugar contra un rival fuerte la fecha posterior a la UEL
    evaluacion += equipo_fuerte_fecha_internacional(rueda1, rueda2, equipos_fuertes, equipos_UEL, fechas_posteriores_UEL)*peso_equipos_fuertes_posterior_UEL;
    //cout << "(C102f) Equipos fuertes posterior UEL: " << equipo_fuerte_fecha_internacional(rueda1, rueda2, equipos_fuertes, equipos_UEL, fechas_posteriores_UEL)*peso_equipos_fuertes_posterior_UEL << endl;

    // revision C103 (100): Equipos emparejados no deben jugar en fechas festivas
    evaluacion += evitar_fechas_festivas_equipos_emparejados(rueda1, rueda2, equipos_emparejados, fecha_boxing_day, fecha_new_year)*peso_equipos_emparejados_fechas_festivas/2;
    //cout << "(C103) Equipos emparejados festivos: " << evitar_fechas_festivas_equipos_emparejados(rueda1, rueda2, equipos_emparejados, fecha_boxing_day, fecha_new_year)*peso_equipos_emparejados_fechas_festivas/2 << endl;

    // revision C12a (90): Equipos no deben jugar en las dos primeras fechaso ultimas fechas como local
    evaluacion += revision_primeras_ultimas_fechas_local(rueda1, rueda2)*peso_break_primeras_ultimas_fechas;
    //cout << "(C12a) Primeras y ultimas fechas local: " << revision_primeras_ultimas_fechas_local(rueda1, rueda2)*peso_break_primeras_ultimas_fechas << endl;

    // revision C12b (90): Equipos no deben jugar en las dos primeras fechaso ultimas fechas como visitante
    evaluacion += revision_primeras_ultimas_fechas_visitante(rueda1, rueda2)*peso_break_primeras_ultimas_fechas;
    //cout << "(C12b) Primeras y ultimas fechas visitante: " << revision_primeras_ultimas_fechas_visitante(rueda1, rueda2)*peso_break_primeras_ultimas_fechas << endl;

    // revision C12c (1000): Equipos no deben jugar en la misma condicion en las fechas festivas
    evaluacion += distinta_condicion_boxingday_newyear(rueda1, rueda2, fecha_boxing_day, fecha_new_year)*peso_condicion_diferente_fechas_festivas;
    //cout << "(C12c) Condicion diferente festivos: " << distinta_condicion_boxingday_newyear(rueda1, rueda2, fecha_boxing_day, fecha_new_year)*peso_condicion_diferente_fechas_festivas << endl;

    // revision C13 (100): Equipos no deben jugar mas de 3 partidos seguidos como local
    evaluacion += local_3partidos(rueda1, rueda2)*peso_maximo_3partidos_local_visitante;
    //cout << "(C13) Local 3 partidos: " << local_3partidos(rueda1, rueda2)*peso_maximo_3partidos_local_visitante << endl;

    // revision C14 (100): Equipos no deben jugar mas de 3 partidos seguidos como visitante
    evaluacion += visitante_3partidos(rueda1, rueda2)*peso_maximo_3partidos_local_visitante;
    //cout << "(C14) Visitante 3 partidos: " << visitante_3partidos(rueda1, rueda2)*peso_maximo_3partidos_local_visitante << endl;

    // revision C105 (2): Equipos no deben juagar como visitante la fecha previa y posterior a FA Cup
    evaluacion += no_jugar_ambos_como_visitante(rueda1, rueda2, fechas_previas_FA_Cup, fechas_posteriores_FA_Cup)*peso_jugar_visitante_FACup;
    //cout << "(C105) Jugar visitante FA Cup: " << no_jugar_ambos_como_visitante(rueda1, rueda2, fechas_previas_FA_Cup, fechas_posteriores_FA_Cup)*peso_jugar_visitante_FACup << endl;

    // revision C106 (50): Balance de partidos como local y visitante
    /*
    int balance_local_visitante_count = 0;
    for (int i = 0; i < fechas_bank_holidays.size(); i++){
        //evaluacion += balance_local_visitante(rueda1, rueda2, fechas_bank_holidays[i])*peso_balance_local_visitante;
        balance_local_visitante_count += balance_local_visitante(rueda1, rueda2, fechas_bank_holidays[i]);
    }
    */
    evaluacion += balance_bank_holidays(rueda1,rueda2,fechas_bank_holidays)*peso_balance_bank_holidays;
    //cout << "(C106) Balance local visitante: " << balance_bank_holidays(rueda1,rueda2,fechas_bank_holidays)*peso_balance_bank_holidays << endl;

    // revision C107 (0.5): Distancias entre equipos
    // si la distancia es menor a lo optimo, no se considera la penalizacion (esto puede suceder cuando hay enfrentamientos entre equipos fuertes o emparejados en fechas festivas)
    if (distancia_festivos(rueda1, rueda2, distancias, fecha_boxing_day, fecha_new_year)-distiancia_optima > 0){
        evaluacion += int((distancia_festivos(rueda1, rueda2, distancias, fecha_boxing_day, fecha_new_year)-distiancia_optima)*peso_distancias);
    }

    // revision C108 (1000): Los mismos equipos no se deben enfrentar en fechas festivas
    evaluacion += rival_boxing_day_new_year_diferente(rueda1, rueda2, fecha_boxing_day, fecha_new_year)*peso_equipos_diferentes_fechas_festivas/2;
    //cout << "(C108) Equipos diferentes festivos: " << rival_boxing_day_new_year_diferente(rueda1, rueda2, fecha_boxing_day, fecha_new_year)*peso_equipos_diferentes_fechas_festivas/2 << endl;

    // revision C19 (60): Distancia de 12 fechas antes de enfrentarse nuevamente al mismo equipo
    evaluacion += distancia_fecha_enfrentarse_nuevamente(rueda1, rueda2, 12)*peso_cant_fechas_rival_nuevamente/2;
    //cout << "(C19) Distancia enfrentarse nuevamente: " << distancia_fecha_enfrentarse_nuevamente(rueda1, rueda2, 12)*peso_cant_fechas_rival_nuevamente/2 << endl;

    //cout << "Evaluacion total: " << evaluacion << endl;

    return evaluacion;
}

void print_costo_restricciones_epl(int distiancia_optima, int fecha_boxing_day, int fecha_new_year, vector<vector<int>> rueda1, vector<vector<int>> rueda2, vector<int> equipos_fuertes, vector<int> equipos_UCL, vector<int> equipos_UEL,
    vector<int> equipos_UECL, vector<int> equipos_emparejados, vector <int >fechas_previas_FA_Cup, vector<int> fechas_posteriores_FA_Cup, vector<int> fechas_previas_UCL,
    vector<int> fechas_posteriores_UCL, vector<int> fechas_previas_UEL, vector<int> fechas_posteriores_UEL, vector<int> fechas_previas_UECL, vector<int> fechas_posteriores_UECL, vector<int> fechas_bank_holidays, 
    vector<vector<int>> solicituedes_visitante, vector<vector<int>> distancias){

        int peso_solicitudes_no_jugar_como_local = 60; //CO4
        int peso_equipos_emparejados_locales = 100; //C07
        int peso_equipos_fuertes_primera_fecha = 80; //C102a
        int peso_equipos_fuertes_fechas_festivas = 90; //C102b
        int peso_equipos_fuertes_previa_UCL = 45; //C102c
        int peso_equipos_fuertes_posterior_UCL = 30; //C102e
        int peso_equipos_fuertes_previa_UEL = 5; //C102d
        int peso_equipos_fuertes_posterior_UEL = 9; //C102f
        int peso_equipos_emparejados_fechas_festivas = 100; //C103
        int peso_break_primeras_ultimas_fechas = 90; //C12a y C12b
        int peso_condicion_diferente_fechas_festivas = 1000; //C12c
        int peso_maximo_3partidos_local_visitante = 100; //C13 y C14
        int peso_jugar_visitante_FACup = 2; //C105
        int peso_balance_bank_holidays = 50; //C106 
        float peso_distancias = 0.5; //C107
        int peso_equipos_diferentes_fechas_festivas = 1000; //C108
        int peso_cant_fechas_rival_nuevamente = 60; //C19
    
        //revision C04 solicitudes visitante
        vector<int> aux_equipos_solicitud_visitante;
        vector<int> aux_fechas_solicitud_visitante;
        for (int i = 0; i < solicituedes_visitante.size(); i++){
            aux_equipos_solicitud_visitante.push_back(solicituedes_visitante[i][0]);
            aux_fechas_solicitud_visitante.push_back(solicituedes_visitante[i][1]);
        }


        cout << "(C04) Solicitudes no jugar como local: " << solicitud_no_jugar_como_local(rueda1, rueda2, aux_equipos_solicitud_visitante, aux_fechas_solicitud_visitante)*peso_solicitudes_no_jugar_como_local << endl;

        cout << "(C07) Equipos emparejados locales: " << evitar_localias_equipos_emparejados(rueda1, rueda2, equipos_emparejados)*peso_equipos_emparejados_locales/2 << endl;

        cout << "(C102a) Equipos fuertes primera fecha: " << enfrentamientos_entre_equipos_fuertes(rueda1, rueda2, equipos_fuertes, 1)*peso_equipos_fuertes_primera_fecha/2 << endl;

        cout << "(C102b) Equipos fuertes festivos: " << enfrentamientos_entre_equipos_fuertes(rueda1, rueda2, equipos_fuertes, fecha_boxing_day)*peso_equipos_fuertes_fechas_festivas/2 + enfrentamientos_entre_equipos_fuertes(rueda1, rueda2, equipos_fuertes, fecha_new_year)*peso_equipos_fuertes_fechas_festivas/2 << endl;

        cout << "(C102c) Equipos fuertes previa UCL: " << equipo_fuerte_fecha_internacional(rueda1, rueda2, equipos_fuertes, equipos_UCL, fechas_previas_UCL)*peso_equipos_fuertes_previa_UCL << endl;
    
        cout << "(C102d) Equipos fuertes previa UEL: " << equipo_fuerte_fecha_internacional(rueda1, rueda2, equipos_fuertes, equipos_UEL, fechas_previas_UEL)*peso_equipos_fuertes_previa_UEL << endl;

        cout << "(C102e) Equipos fuertes posterior UCL: " << equipo_fuerte_fecha_internacional(rueda1, rueda2, equipos_fuertes, equipos_UCL, fechas_posteriores_UCL)*peso_equipos_fuertes_posterior_UCL << endl;

        cout << "(C102f) Equipos fuertes posterior UEL: " << equipo_fuerte_fecha_internacional(rueda1, rueda2, equipos_fuertes, equipos_UEL, fechas_posteriores_UEL)*peso_equipos_fuertes_posterior_UEL << endl;

        cout << "(C103) Equipos emparejados festivos: " << evitar_fechas_festivas_equipos_emparejados(rueda1, rueda2, equipos_emparejados, fecha_boxing_day, fecha_new_year)*peso_equipos_emparejados_fechas_festivas/2 << endl;

        cout << "(C12a) Primeras y ultimas fechas local: " << revision_primeras_ultimas_fechas_local(rueda1, rueda2)*peso_break_primeras_ultimas_fechas << endl;

        cout << "(C12b) Primeras y ultimas fechas visitante: " << revision_primeras_ultimas_fechas_visitante(rueda1, rueda2)*peso_break_primeras_ultimas_fechas << endl;

        cout << "(C12c) Condicion diferente festivos: " << distinta_condicion_boxingday_newyear(rueda1, rueda2, fecha_boxing_day, fecha_new_year)*peso_condicion_diferente_fechas_festivas << endl;

        cout << "(C13) Local 3 partidos: " << local_3partidos(rueda1, rueda2)*peso_maximo_3partidos_local_visitante << endl;

        cout << "(C14) Visitante 3 partidos: " << visitante_3partidos(rueda1, rueda2)*peso_maximo_3partidos_local_visitante << endl;

        cout << "(C105) Jugar visitante FA Cup: " << no_jugar_ambos_como_visitante(rueda1, rueda2, fechas_previas_FA_Cup, fechas_posteriores_FA_Cup)*peso_jugar_visitante_FACup << endl;
    
        int balance_local_visitante_count = 0;
        for (int i = 0; i < fechas_bank_holidays.size(); i++){
            balance_local_visitante_count += balance_local_visitante(rueda1, rueda2, fechas_bank_holidays[i]);
        }
        cout << "(C106) Balance local visitante: " << balance_bank_holidays(rueda1,rueda2,fechas_bank_holidays)*peso_balance_bank_holidays << endl;

        cout << "(C107) Distancias: " << (distancia_festivos(rueda1, rueda2, distancias, fecha_boxing_day, fecha_new_year)-distiancia_optima)*peso_distancias << endl;

        cout << "(C108) Equipos diferentes festivos: " << rival_boxing_day_new_year_diferente(rueda1, rueda2, fecha_boxing_day, fecha_new_year)*peso_equipos_diferentes_fechas_festivas/2 << endl;

        cout << "(C19) Distancia enfrentarse nuevamente: " << distancia_fecha_enfrentarse_nuevamente(rueda1, rueda2, 12)*peso_cant_fechas_rival_nuevamente/2 << endl;
}

int funcion_evaluacion_pdc(vector<vector<int>> rueda1, vector<vector<int>> rueda2, int fecha_limite_vacaciones, vector<int> equipos_fuertes, vector<int> equipos_libertadores, vector<int> equipos_prelibertadores, 
    vector<int> equipos_sudamericana, vector<int> equipos_zona_norte, vector<int> equipos_zona_centro, vector<int> equipos_zona_sur, vector<int> equipos_zona_vacaciones, vector<int> equipos_santiago,
    vector<int> fechas_previas_prelibertadores, vector<int> fechas_posteriores_prelibertadores, vector<int> fechas_previas_libertadores, vector<int> fechas_posteriores_libertadores, vector<int> fechas_previas_sudamericana,
    vector<int> fechas_posteriores_sudamericana, vector<vector<int>> solicituedes_visitante){

    //Copiando pesos de la variante EPL para las restricciones comunes o similares

    int evaluacion = 0;

    int peso_solicitudes_no_jugar_como_local = 60; //C04
    int peso_break_primeras_ultimas_fechas = 90; //C12a y C12b
    int peso_maximo_3partidos_local_visitante = 100; //C13 y C14
    int peso_cant_fechas_rival_nuevamente = 60; //C19

    int peso_equipos_fuertes_previa_prelibertadores = 15; //C208a
    int peso_equipos_fuertes_posterior_prelibertadores = 15; //C208b
    int peso_equipos_fuertes_previa_libertadores = 60; //C208c
    int peso_equipos_fuertes_posterior_libertadores = 55; //C208d
    int peso_equipos_fuertes_previa_sudamericana = 20; //C208e
    int peso_equipos_fuertes_posterior_sudamericana = 20; //C208f

    int peso_equipos_zonas = 50; //C205a, C205b, C205c
    int peso_equipos_fuertes_primeras_ultimas_fechas = 80; //C203

    int peso_localias_clasicos = 100; //C204

    int peso_enfrentamientos_consecutivos_fuertes = 70; //C201

    int peso_vacaciones_equipos_fuertes = 30; //C207

    int peso_partidos_santiago = 50; //C207

    int peso_balance_localias_rueda = 200; //C202

    //generando vectores para solicitudes de no jugar como local
    vector<int> aux_equipos_solicitud_visitante;
    vector<int> aux_fechas_solicitud_visitante;
    for (int i = 0; i < solicituedes_visitante.size(); i++){
        aux_equipos_solicitud_visitante.push_back(solicituedes_visitante[i][0]);
        aux_fechas_solicitud_visitante.push_back(solicituedes_visitante[i][1]);
    }

    /*
    // imprimir equipos solicitados a no jugar como local
    //cout << "Equipos solicitados a no jugar como local: ";
    for (int i = 0; i < aux_equipos_solicitud_visitante.size(); i++){
        cout << aux_equipos_solicitud_visitante[i] << " ";
    }
    cout << endl;

    // imprimir fechas solicitadas a no jugar como local
    //cout << "Fechas solicitadas a no jugar como local: ";
    for (int i = 0; i < aux_fechas_solicitud_visitante.size(); i++){
        cout << aux_fechas_solicitud_visitante[i] << " ";
    }
    cout << endl;
    */
    

    // ejemplos peso torneos internacionales
    //int peso_equipos_fuertes_previa_UCL = 45; //C102c
    //int peso_equipos_fuertes_posterior_UCL = 30; //C102e
    //int peso_equipos_fuertes_previa_UEL = 5; //C102d
    //int peso_equipos_fuertes_posterior_UEL = 9; //C102f

    //cout << "Evaluacion de las restricciones: ------------------------------------------------------------------------------------------------" << endl;

    //R1

    //cout << solicitud_no_jugar_como_local(rueda1, rueda2, aux_equipos_solicitud_visitante, aux_fechas_solicitud_visitante) << endl;

    evaluacion += solicitud_no_jugar_como_local(rueda1, rueda2, aux_equipos_solicitud_visitante, aux_fechas_solicitud_visitante)*peso_solicitudes_no_jugar_como_local;

    //cout << "Hola" << endl;

    //R2 y R3
    evaluacion += revision_primeras_ultimas_fechas_local(rueda1, rueda2)*peso_break_primeras_ultimas_fechas;
    evaluacion += revision_primeras_ultimas_fechas_visitante(rueda1, rueda2)*peso_break_primeras_ultimas_fechas;

    //R4
    evaluacion += local_3partidos(rueda1, rueda2)*peso_maximo_3partidos_local_visitante;
    evaluacion += visitante_3partidos(rueda1, rueda2)*peso_maximo_3partidos_local_visitante;

    //R5
    evaluacion += distancia_fecha_enfrentarse_nuevamente(rueda1, rueda2, 10)*peso_cant_fechas_rival_nuevamente/2;

    //R6.1
    evaluacion += equipo_fuerte_fecha_internacional(rueda1, rueda2, equipos_fuertes, equipos_prelibertadores, fechas_previas_prelibertadores)*peso_equipos_fuertes_previa_prelibertadores;

    //R6.2
    evaluacion += equipo_fuerte_fecha_internacional(rueda1, rueda2, equipos_fuertes, equipos_prelibertadores, fechas_posteriores_prelibertadores)*peso_equipos_fuertes_posterior_prelibertadores;

    //R6.3
    evaluacion += equipo_fuerte_fecha_internacional(rueda1, rueda2, equipos_fuertes, equipos_libertadores, fechas_previas_libertadores)*peso_equipos_fuertes_previa_libertadores;

    //R6.4
    evaluacion += equipo_fuerte_fecha_internacional(rueda1, rueda2, equipos_fuertes, equipos_libertadores, fechas_posteriores_libertadores)*peso_equipos_fuertes_posterior_libertadores;

    //R6.5
    evaluacion += equipo_fuerte_fecha_internacional(rueda1, rueda2, equipos_fuertes, equipos_sudamericana, fechas_previas_sudamericana)*peso_equipos_fuertes_previa_sudamericana;
    
    //R6.6
    evaluacion += equipo_fuerte_fecha_internacional(rueda1, rueda2, equipos_fuertes, equipos_sudamericana, fechas_posteriores_sudamericana)*peso_equipos_fuertes_posterior_sudamericana;

    //R7
    evaluacion += revision_equipos_zona(rueda1, rueda2, equipos_zona_norte, equipos_zona_centro, equipos_zona_sur)*peso_equipos_zonas;

    //R8
    vector<int> fechas_evitar_fuertes = {1,2,3,28,29,30};
    evaluacion += enfrentamientos_entre_equipos_fuertes(rueda1, rueda2, equipos_fuertes, fechas_evitar_fuertes)*peso_equipos_fuertes_primeras_ultimas_fechas/2;

    //R9
    evaluacion += clasicos_local_visitante(rueda1, rueda2, equipos_fuertes)*peso_localias_clasicos;

    //R10
    evaluacion += fechas_consecutivas_equipos_fuertes(rueda1, rueda2, equipos_fuertes)*peso_enfrentamientos_consecutivos_fuertes;

    //R11
    evaluacion += equipos_zonas_vacaciones(rueda1, equipos_zona_vacaciones, equipos_fuertes, fecha_limite_vacaciones)*peso_vacaciones_equipos_fuertes;

    //R12
    evaluacion += equipos_local_simultaneo(rueda1, rueda2, equipos_santiago,2,4)*peso_partidos_santiago;

    //R13
    evaluacion += balance_localias_rueda(rueda1)*peso_balance_localias_rueda;

    return evaluacion;
}

void print_costo_restricciones_pdc(vector<vector<int>> rueda1, vector<vector<int>> rueda2, int fecha_limite_vacaciones, vector<int> equipos_fuertes, vector<int> equipos_libertadores, vector<int> equipos_prelibertadores, 
    vector<int> equipos_sudamericana, vector<int> equipos_zona_norte, vector<int> equipos_zona_centro, vector<int> equipos_zona_sur, vector<int> equipos_zona_vacaciones, vector<int> equipos_santiago,
    vector<int> fechas_previas_prelibertadores, vector<int> fechas_posteriores_prelibertadores, vector<int> fechas_previas_libertadores, vector<int> fechas_posteriores_libertadores, vector<int> fechas_previas_sudamericana,
    vector<int> fechas_posteriores_sudamericana, vector<vector<int>> solicituedes_visitante){

    int peso_solicitudes_no_jugar_como_local = 60; //C04
    int peso_break_primeras_ultimas_fechas = 90; //C12a y C12b
    int peso_maximo_3partidos_local_visitante = 100; //C13 y C14
    int peso_cant_fechas_rival_nuevamente = 60; //C19

    int peso_equipos_fuertes_previa_prelibertadores = 15; //C208a
    int peso_equipos_fuertes_posterior_prelibertadores = 15; //C208b
    int peso_equipos_fuertes_previa_libertadores = 60; //C208c
    int peso_equipos_fuertes_posterior_libertadores = 55; //C208d
    int peso_equipos_fuertes_previa_sudamericana = 20; //C208e
    int peso_equipos_fuertes_posterior_sudamericana = 20; //C208f

    int peso_equipos_zonas = 50; //C205a, C205b, C205c
    int peso_equipos_fuertes_primeras_ultimas_fechas = 80; //C203

    int peso_localias_clasicos = 100; //C204

    int peso_enfrentamientos_consecutivos_fuertes = 70; //C201

    int peso_vacaciones_equipos_fuertes = 30; //C207

    int peso_partidos_santiago = 50; //C207

    int peso_balance_localias_rueda = 200; //C202

    //generando vectores para solicitudes de no jugar como local
    vector<int> aux_equipos_solicitud_visitante;
    vector<int> aux_fechas_solicitud_visitante;
    for (int i = 0; i < solicituedes_visitante.size(); i++){
        aux_equipos_solicitud_visitante.push_back(solicituedes_visitante[i][0]);
        aux_fechas_solicitud_visitante.push_back(solicituedes_visitante[i][1]);
    }

    cout << "(C04) Solicitudes no jugar como local: " << solicitud_no_jugar_como_local(rueda1, rueda2, aux_equipos_solicitud_visitante, aux_fechas_solicitud_visitante)*peso_solicitudes_no_jugar_como_local << endl;

    cout << "(C12a) Primeras y ultimas fechas local: " << revision_primeras_ultimas_fechas_local(rueda1, rueda2)*peso_break_primeras_ultimas_fechas << endl;

    cout << "(C12b) Primeras y ultimas fechas visitante: " << revision_primeras_ultimas_fechas_visitante(rueda1, rueda2)*peso_break_primeras_ultimas_fechas << endl;

    cout << "(C13) Local 3 partidos: " << local_3partidos(rueda1, rueda2)*peso_maximo_3partidos_local_visitante << endl;

    cout << "(C14) Visitante 3 partidos: " << visitante_3partidos(rueda1, rueda2)*peso_maximo_3partidos_local_visitante << endl;

    cout << "(C19) Distancia enfrentarse nuevamente: " << distancia_fecha_enfrentarse_nuevamente(rueda1, rueda2, 10)*peso_cant_fechas_rival_nuevamente/2 << endl;

    cout << "(C208a) Equipos fuertes previa prelibertadores: " << equipo_fuerte_fecha_internacional(rueda1, rueda2, equipos_fuertes, equipos_prelibertadores, fechas_previas_prelibertadores)*peso_equipos_fuertes_previa_prelibertadores << endl;

    cout << "(C208b) Equipos fuertes posterior prelibertadores: " << equipo_fuerte_fecha_internacional(rueda1, rueda2, equipos_fuertes, equipos_prelibertadores, fechas_posteriores_prelibertadores)*peso_equipos_fuertes_posterior_prelibertadores << endl;

    cout << "(C208c) Equipos fuertes previa libertadores: " << equipo_fuerte_fecha_internacional(rueda1, rueda2, equipos_fuertes, equipos_libertadores, fechas_previas_libertadores)*peso_equipos_fuertes_previa_libertadores << endl;

    cout << "(C208d) Equipos fuertes posterior libertadores: " << equipo_fuerte_fecha_internacional(rueda1, rueda2, equipos_fuertes, equipos_libertadores, fechas_posteriores_libertadores)*peso_equipos_fuertes_posterior_libertadores << endl;

    cout << "(C208e) Equipos fuertes previa sudamericana: " << equipo_fuerte_fecha_internacional(rueda1, rueda2, equipos_fuertes, equipos_sudamericana, fechas_previas_sudamericana)*peso_equipos_fuertes_previa_sudamericana << endl;

    cout << "(C208f) Equipos fuertes posterior sudamericana: " << equipo_fuerte_fecha_internacional(rueda1, rueda2, equipos_fuertes, equipos_sudamericana, fechas_posteriores_sudamericana)*peso_equipos_fuertes_posterior_sudamericana << endl;

    cout << "(C205a + C205b + C205c) Equipos zonas: " << revision_equipos_zona(rueda1, rueda2, equipos_zona_norte, equipos_zona_centro, equipos_zona_sur)*peso_equipos_zonas << endl;

    vector<int> fechas_evitar_fuertes = {1,2,3,28,29,30};
    cout << "(C203) Equipos fuertes primeras 3 y ultimas 3 fechas: " << enfrentamientos_entre_equipos_fuertes(rueda1, rueda2, equipos_fuertes, fechas_evitar_fuertes)*peso_equipos_fuertes_primeras_ultimas_fechas/2 << endl;

    cout << "(C204) Localias clasicos: " << clasicos_local_visitante(rueda1, rueda2, equipos_fuertes)*peso_localias_clasicos << endl;

    cout << "(C201) Enfrentamientos consecutivos fuertes: " << fechas_consecutivas_equipos_fuertes(rueda1, rueda2, equipos_fuertes)*peso_enfrentamientos_consecutivos_fuertes << endl;

    cout << "(C207) Equipos zonas vacaciones: " << equipos_zonas_vacaciones(rueda1, equipos_zona_vacaciones, equipos_fuertes, fecha_limite_vacaciones)*peso_vacaciones_equipos_fuertes << endl;

    cout << "(C206) Partidos Santiago: " << equipos_local_simultaneo(rueda1, rueda2, equipos_santiago,2,4)*peso_partidos_santiago << endl;

    cout << "(C202) Balance localias rueda: " << balance_localias_rueda(rueda1)*peso_balance_localias_rueda << endl;
}
