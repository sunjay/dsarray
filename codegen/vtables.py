#!/usr/bin/env python3

INT_TYPES = [
    ("int8_t", "d"),
    ("int16_t", "d"),
    ("int32_t", "d"),
    ("int64_t", "ld"),
    ("uint8_t", "u"),
    ("uint16_t", "u"),
    ("uint32_t", "u"),
    ("uint64_t", "lu"),
    ("char", "c"),
    ("size_t", "zu"),
]

FLOAT_TYPES = [
    "float",
    "double",
]

BOOL_TYPES = [
    "bool",
]

FILE_TYPES = [
    "file",
]

INT_VTABLE_TEMPLATE = """\
///////// vtable for {type_name} /////////
static int8_t cmp_{type_name}(void *a, void *b) {{
    {type_name} *ta = a;
    {type_name} *tb = b;
    return *ta - *tb;
}}
static bool eq_{type_name}(void *a, void *b) {{
    {type_name} *ta = a;
    {type_name} *tb = b;
    return *ta == *tb;
}}
static void print_{type_name}(void *a) {{
    {type_name} *ta = a;
    printf("%{format_specifier}", *ta);
}}
dsvtable vtable_{type_name} = {{
    .cmp = cmp_{type_name},
    .eq = eq_{type_name},
    .print = print_{type_name},
}};
"""

FLOAT_VTABLE_TEMPLATE = """\
///////// vtable for {type_name} /////////
static int8_t cmp_{type_name}(void *a, void *b) {{
    {type_name} *ta = a;
    {type_name} *tb = b;
    if (*ta < *tb) {{
        return -1;
    }} else if (*ta > *tb) {{
        return 1;
    }} else {{ // *ta == *tb
        return 0;
    }}
}}
static bool eq_{type_name}(void *a, void *b) {{
    {type_name} *ta = a;
    {type_name} *tb = b;
    return *ta == *tb;
}}
static void print_{type_name}(void *a) {{
    {type_name} *ta = a;
    printf("%g", *ta);
}}
dsvtable vtable_{type_name} = {{
    .cmp = cmp_{type_name},
    .eq = eq_{type_name},
    .print = print_{type_name},
}};
"""

BOOL_VTABLE_TEMPLATE = """\
///////// vtable for {type_name} /////////
static bool eq_{type_name}(void *a, void *b) {{
    {type_name} *ta = a;
    {type_name} *tb = b;
    return *ta == *tb;
}}
static void print_{type_name}(void *a) {{
    {type_name} *ta = a;
    printf("%s", *ta ? "true" : "false");
}}
dsvtable vtable_{type_name} = {{
    .eq = eq_{type_name},
    .print = print_{type_name},
}};
"""

FILE_VTABLE_TEMPLATE = """\
///////// vtable for {type_name} /////////
static void drop_{type_name}(void *a) {{
    FILE **ta = a;
    fclose(*ta);
}}
dsvtable vtable_{type_name} = {{
    .drop = drop_{type_name},
}};
"""

def main():
    for type_name, format_specifier in INT_TYPES:
        print(INT_VTABLE_TEMPLATE.format(
            type_name=type_name,
            format_specifier=format_specifier,
        ))

    for type_name in FLOAT_TYPES:
        print(FLOAT_VTABLE_TEMPLATE.format(
            type_name=type_name,
        ))

    for type_name in BOOL_TYPES:
        print(BOOL_VTABLE_TEMPLATE.format(
            type_name=type_name,
        ))

    for type_name in FILE_TYPES:
        print(FILE_VTABLE_TEMPLATE.format(
            type_name=type_name,
        ))

if __name__ == "__main__":
    main()
