/*
 *
 * Std_Reader.c
 *
 * Copyright 2019 Yuichi Yoshii
 *     吉井雄一 @ 吉井産業  you.65535.kir@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "Std_Reader.h"

void std_reader_fetch(Std_Reader * r) {
    errno = 0;
    r->arg = (char **) malloc(sizeof(char *) * r->count);
    if (NULL == r->arg) {
        return;
    }
    for (int i = 0; r->count > i; ++i) {
        r->arg[i] = (char *) malloc((size_t) r->size + 1);
        if (NULL == r->arg[i]) {
            return;
        }
        for (int j = 0; r->size > j; ++j) {
            r->arg[i][j] = 0;
        }
    }
    char f[8];
    snprintf(f, 8, "%%%ds", r->size);
    for (int k = 0; r->count > k; ++k) {
        scanf(f, r->arg[k]);
    }
}

char ** std_reader_get(Std_Reader * r) {
    return r->arg;
}

char ** std_reader_clone(Std_Reader * r) {
    errno = 0;
    char ** ret = (char **) malloc(sizeof(char *) * r->count);
    if (NULL == ret) {
        return NULL;
    }
    for (int i = 0; r->count > i; ++i) {
        ret[i] = (char *) malloc((size_t) r->size + 1);
        if (NULL == ret[i]) {
            return NULL;
        }
        for (int j = 0; r->size > j; ++j) {
            ret[i][j] = r->arg[i][j];
        }
        ret[i][r->size] = 0;
    }
    return ret;
}

void std_reader_dispose(Std_Reader * r) {
    errno = 0;
    for (int i = 0; r->count > i; ++i) {
        free(r->arg[i]);
    }
    free(r->arg);
}

Std_Reader * Std_Reader_init(Std_Reader * r, int s, int c) {
    r->size = s;
    r->count = c;
    r->arg = NULL;
    r->fetch = std_reader_fetch;
    r->get = std_reader_get;
    r->clone = std_reader_clone;
    r->dispose = std_reader_dispose;
    return r;
}

void Std_Reader_dispose_clone(char ** arg, int c) {
    errno = 0;
    for (int i = 0; c > i; ++i) {
        free(arg[i]);
    }
    free(arg);
}