/*
 * Copyright 2015 Wink Saville
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
 */

#include "inttypes.h"
#include "abort.h"
#include "gdt.h"
#include "regs_x86_64.h"
#include "print.h"
#include "descriptors_x86_64_print.h"
#include "test_print.h"
#include "test_registers.h"
#include "test_multiboot.h"
#include "test_interrupts.h"
#include "interrupts.h"

__attribute__ ((__noreturn__))
void kmain(void* mb_info) {
  initialize_gdt();

  initialize_intr_trap_table();

  test_print();

  test_registers();

  test_multiboot(mb_info);

  test_interrupts();

  print_nl();
  print_str_nl("SUCCESS");

  abort();
}
