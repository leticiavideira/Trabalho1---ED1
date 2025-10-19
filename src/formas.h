enum formaTipo {CIRCLE, RECTANGLE, LINE, TEXT, TEXT_STYLE};

typedef enum formaTipo formaTipo;

typedef struct{
    formaTipo tipoF;
    void* data;
} FormaSt;