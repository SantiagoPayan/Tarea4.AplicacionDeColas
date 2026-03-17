# Tarea4.AplicacionDeColas

# Tarea 4: Simulación de Banco con Colas (Queue) 🏦

Este proyecto es una simulación en tiempo real de la atención a clientes en un banco utilizando **C++**. Implementa una estructura de datos de **Cola (Queue)** basada en una **lista enlazada circular**, asegurando un manejo de memoria eficiente y dinámico.

## 👥 Autores
* **Santiago Payan Ibarra**
* **Jose Maria Nuñez Saille**

## 🚀 Características Principales
* **Cola Circular Personalizada:** Implementación desde cero de una plantilla `Queue<T>` con un único puntero al final (`found`) para mantener el comportamiento circular.
* **Simulación Aleatoria:** El tiempo total de apertura del banco (120 - 240 minutos), el tiempo de atención por caja (2 - 8 minutos) y la llegada de clientes se generan de forma dinámica usando `<cstdlib>`.
* **Interfaz en Tiempo Real:** El programa actualiza la terminal simulando el paso del reloj minuto a minuto, mostrando el estado de las 3 cajas y la fila de espera.
* **Lectura de Archivos:** Carga automática de nombres de clientes reales desde un archivo de texto (`nombres.txt`).
* **Resumen Final:** Al cerrar el banco, el sistema imprime un historial detallado de qué clientes fueron atendidos por cada caja y quiénes se quedaron en la fila de espera.

## 📁 Estructura del Proyecto
El proyecto sigue el estándar de separación de archivos de C++:
```text
queue-for-bank/
├── README.md
├── bitacora_tarea4.txt
├── .vscode/
│   └── tasks.json
└── src/
    ├── main.cpp
    ├── Bank.cpp
    ├── nombres.txt
    ├── headers/
    │   ├── Bank.hpp
    │   └── Queue.hpp
    └── templates/
        └── Queue.tpp
