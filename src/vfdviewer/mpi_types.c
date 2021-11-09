#define NUM_MPI_TYPES 38

const char* const all_mpi_types[NUM_MPI_TYPES] = {
   "MPI_CHAR",
   "MPI_SHORT",
   "MPI_INT",
   "MPI_LONG",
   "MPI_LONG_LONG_INT",
   "MPI_LONG_LONG",
   "MPI_SIGNED_CHAR",
   "MPI_UNSIGNED_CHAR",
   "MPI_UNSIGNED_SHORT",
   "MPI_UNSIGNED",
   "MPI_UNSIGNED_LONG",
   "MPI_UNSIGNED_LONG_LONG",
   "MPI_FLOAT",
   "MPI_DOUBLE",
   "MPI_LONG_DOUBLE",
   "MPI_WCHAR",
   "MPI_C_BOOL",
   "MPI_INT8_T",
   "MPI_INT16_T",
   "MPI_INT32_T",
   "MPI_INT64_T",
   "MPI_UINT8_T",
   "MPI_UINT16_T",
   "MPI_UINT32_T",
   "MPI_UINT64_T",
   "MPI_C_COMPLEX",
   "MPI_C_FLOAT_COMPLEX",
   "MPI_C_DOUBLE_COMPLEX",
   "MPI_C_LONG_DOUBLE_COMPLEX",
   "MPI_INTEGER",
   "MPI_LOGICAL",
   "MPI_REAL",
   "MPI_DOUBLE_PRECISION",
   "MPI_COMPLEX",
   "MPI_CHARACTER",
   "MPI_BYTE",
   "MPI_PACKED"
};

const char *get_mpitype_string_from_idx(int mpi_type_idx) {
   if (mpi_type_idx >= 0 && mpi_type_idx < NUM_MPI_TYPES) {
      return all_mpi_types[mpi_type_idx];
   } else if (mpi_type_idx == -1) {
      return "MPI_DERIVED_TYPE";
   } else {
      return "MPI_UNDEFINED_TYPE";
   }
}
