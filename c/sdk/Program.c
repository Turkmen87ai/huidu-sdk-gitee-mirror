#include "Program.h"

ProgramClient* createProgramClient() {
    ProgramClient* program = (ProgramClient*)hdmalloc(sizeof(ProgramClient));
    if (!program) {
        return NULL;
    }
    program->baseClient = createBaseClient();
    program->dataEx = NULL;

    if (!program->baseClient) {
        hdfree(program);
        return NULL;
    }

    return program;
}

void destroyProgramClient(ProgramClient* program) {
    if (program) {
        destroyBaseClient(program->baseClient);
        if (program->dataEx) {
			free(program->dataEx);
		}
        hdfree(program);
    }
}

void setDataExProgramClient(ProgramClient* program, const char* dataEx) {
    if (!program) {
        return;
    }

    if (program->dataEx) {
        hdfree(program->dataEx);
        program->dataEx = NULL;
    }

    if (dataEx) {
        program->dataEx = strdup(dataEx);
    }
}

char* appendProgramClient(ProgramClient* program, const char** ids, int idCount,
    ProgramNode** nodes, int nodeCount) {
    if (!program || !program->baseClient || !ids || idCount <= 0 || !nodes || nodeCount <= 0) {
        return NULL;
    }

    return programBaseClient(program->baseClient, ids, idCount, "append",
        (ProgramNode**)nodes, nodeCount, program->dataEx);
}

char* appendSingleProgramClient(ProgramClient* program, const char** ids, int idCount,
    ProgramNode* node) {
    ProgramNode* nodes[] = { node };
    return appendProgramClient(program, ids, idCount, nodes, 1);
}

char* updateProgramClient(ProgramClient* program, const char** ids, int idCount,
    ProgramNode** nodes, int nodeCount) {
    if (!program || !program->baseClient || !ids || idCount <= 0 || !nodes || nodeCount <= 0) {
        return NULL;
    }

    return programBaseClient(program->baseClient, ids, idCount, "update",
        (ProgramNode**)nodes, nodeCount, program->dataEx);
}

char* updateSingleProgramClient(ProgramClient* program, const char** ids, int idCount,
    ProgramNode* node) {
    ProgramNode* nodes[] = { node };
    return updateProgramClient(program, ids, idCount, nodes, 1);
}

char* replaceProgramClient(ProgramClient* program, const char** ids, int idCount,
    ProgramNode** nodes, int nodeCount) {
    if (!program || !program->baseClient || !ids || idCount <= 0 || !nodes || nodeCount <= 0) {
        return NULL;
    }

    return programBaseClient(program->baseClient, ids, idCount, "replace",
        (ProgramNode**)nodes, nodeCount, program->dataEx);
}

char* replaceSingleProgramClient(ProgramClient* program, const char** ids, int idCount,
    ProgramNode* node) {
    ProgramNode* nodes[] = { node };
    return replaceProgramClient(program, ids, idCount, nodes, 1);
}

char* removeProgramClient(ProgramClient* program, const char** ids, int idCount,
    const char** programIds, int programIdCount) {
    if (!program || !program->baseClient || !ids || idCount <= 0 ||
        !programIds || programIdCount <= 0) {
        return NULL;
    }

    ProgramNode** nodes = (ProgramNode**)hdmalloc(programIdCount * sizeof(ProgramNode*));
    if (!nodes) {
        return NULL;
    }

    for (int i = 0; i < programIdCount; i++) {
        nodes[i] = createProgramNode();
        setIdContentNode(nodes[i]->base, programIds[i]);
    }

    char* result = programBaseClient(program->baseClient, ids, idCount, "remove",
        (ProgramNode**)nodes, programIdCount, program->dataEx);

    for (int i = 0; i < programIdCount; i++) {
        destroyProgramNode(nodes[i]);
    }
    hdfree(nodes);

    return result;
}

char* getProgramIdsProgramClient(ProgramClient* program, const char** ids, int idCount) {
    if (!program || !program->baseClient || !ids || idCount <= 0) {
        return NULL;
    }

    return programBaseClient(program->baseClient, ids, idCount, "getAll",
        NULL, 0, NULL);
}

