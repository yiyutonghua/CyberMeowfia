#!/usr/bin/env python3
"""从 BTF textproto 提取 struct 字段偏移."""
import re
import sys
from pathlib import Path

BTF_PATH = Path("/tmp/turbo6v-kernel/android/abi_gki_aarch64.stg")

def parse_btf(path):
    text = path.read_text()
    blocks = re.split(r'\n(?=[a-z_]+ \{)', text)
    types = {}
    for blk in blocks:
        m = re.match(r'(\w+) \{', blk)
        if not m:
            continue
        kind = m.group(1)
        if kind not in ('int', 'pointer_reference', 'array', 'struct', 'union', 'enum', 'fwd', 'typedef', 'volatile', 'const', 'restrict', 'func', 'func_proto', 'var', 'datasec', 'float', 'decl_tag', 'type_tag', 'enum64'):
            continue
        id_m = re.search(r'^  id: (0x[0-9a-f]+)', blk, re.M)
        if not id_m:
            continue
        type_id = int(id_m.group(1), 16)
        name_m = re.search(r'^  name: "([^"]*)"', blk, re.M)
        name = name_m.group(1) if name_m else None
        size_m = re.search(r'^  size: (\d+)', blk, re.M)
        size = int(size_m.group(1)) if size_m else 0
        info = {'kind': kind, 'name': name, 'size': size, 'members': []}
        for mm in re.finditer(r'member \{\s*name: "([^"]*)"\s*type_id: (0x[0-9a-f]+)(?:\s*bits_offset: (\d+))?(?:\s*bits_size: \d+)?', blk):
            mname = mm.group(1)
            mtype = int(mm.group(2), 16)
            after = blk[mm.end():mm.end()+200]
            offm = re.search(r'offset: (\d+)', after)
            if offm:
                moff = int(offm.group(1))
            else:
                boffm = re.search(r'bits_offset: (\d+)', after)
                if boffm:
                    moff = int(boffm.group(1))
                else:
                    moff = -1
            info['members'].append((mname, moff, mtype))
        types[type_id] = info
    return types

def compute_struct_offsets(struct_name, types):
    target_id = None
    for tid, info in types.items():
        if info['kind'] == 'struct' and info['name'] == struct_name:
            target_id = tid
            break
    if target_id is None:
        print(f"not found: {struct_name}", file=sys.stderr)
        return None
    info = types[target_id]
    result = []
    for mname, moff, mtype in info['members']:
        if moff < 0:
            continue
        result.append((mname, moff // 8))
    return result, info.get('size', 0)

if __name__ == "__main__":
    print("parsing BTF...", file=sys.stderr)
    types = parse_btf(BTF_PATH)
    print(f"  parsed {len(types)} types", file=sys.stderr)
    for name in sys.argv[1:]:
        r = compute_struct_offsets(name, types)
        if r:
            fields, sz = r
            print(f"\nstruct {name} (size={sz} = 0x{sz:x}):")
            for fname, off in fields:
                print(f"  +0x{off:04x} ({off:5d}) {fname}")
