/*
 * Copyright 2016 Wink Saville
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
#include "print.h"
#include "descriptors_x86_64.h"
#include "descriptors_x86_64_print.h"

/* Interrupt Descriptor Table */
intr_trap_gate idt[256];

__attribute__ ((__interrupt__, __used__))
void intr_undefined(struct intr_frame *frame) {
  print_intr_frame("intr_undefined:", frame);
}

__attribute__ ((__interrupt__, __used__))
void expt_undefined(struct intr_frame *frame, u64 error_code) {
  print_intr_frame("expt_undefined:", frame);
  print_u64_nl(" error_code=", error_code);
}

__attribute__ ((__interrupt__, __used__))
void expt_invalid_opcode(struct intr_frame *frame, u64 error_code) {
  print_intr_frame("expt_invalid_opcode:", frame);
  print_u64_nl(" error_code=", error_code);
}

void initialize_intr_trap_table() {
  // Initialize to undefined intr
  for (u64 idx = 0; idx < ARRAY_COUNT(idt); idx++) {
    setidt_intr(idt, idx, intr_undefined);
  }

  // Initialize some exceptions
  setidt_expt(idt, 6, expt_invalid_opcode);

  // set the idtr
  setidtr(idt, ARRAY_COUNT(idt));
}