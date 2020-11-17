//make by javaloader 17/11/2020
struct region_t {
    uintptr_t start;
    uintptr_t end;
};

vector<region_t> GetCAllocMaps() {
    vector<region_t> tmp;

    FILE *f = fopen("/proc/self/maps", "r");
    if (f) {
        char line[512];
        while (fgets(line, 512, f)) {
            if (strstr(line, "[anon:libc_malloc]")) {
                region_t reg{0, 0};
                sscanf(line, "%"
                             PRIXPTR
                             "-%"
                             PRIXPTR
                             " %*s %*s %*s %*s %*s", &reg.start, &reg.end);

                tmp.push_back(reg);
            }
        }
        fclose(f);
    }

    return tmp;
}