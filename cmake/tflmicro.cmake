add_library(tflmicro "")

target_include_directories(tflmicro
  PUBLIC
  ${CMAKE_SOURCE_DIR}/lib/
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/DSP/Include
  ${CMAKE_SOURCE_DIR}/lib/third_party/ruy
  ${CMAKE_SOURCE_DIR}/lib/third_party/gemmlowp
  ${CMAKE_SOURCE_DIR}/lib/third_party/kissfft
  ${CMAKE_SOURCE_DIR}/lib/third_party/flatbuffers
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/Core/Include
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis
  ${CMAKE_SOURCE_DIR}/lib/third_party/flatbuffers/include
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Include
)

target_compile_definitions(
  tflmicro
  PUBLIC
  COMPILE_DEFINITIONS TF_LITE_DISABLE_X86_NEON=1
  COMPILE_DEFINITIONS TF_LITE_STATIC_MEMORY=1
  COMPILE_DEFINITIONS CMSIS_NN=1
)

set_target_properties(
  tflmicro
  PROPERTIES
  COMPILE_FLAGS -fno-rtti
  COMPILE_FLAGS -fno-exceptions
  COMPILE_FLAGS -fno-threadsafe-statics
  COMPILE_FLAGS -nostdlib
)

target_link_libraries(
  tflmicro
  pico_stdlib
)

target_sources(tflmicro
  PUBLIC
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/c/common.c
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/core/api/error_reporter.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/core/api/flatbuffer_conversions.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/core/api/op_resolver.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/core/api/tensor_utils.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/quantization_util.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/kernel_util.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/all_ops_resolver.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/activations.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/arg_min_max.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/ceil.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/circular_buffer.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/cmsis-nn/add.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/cmsis-nn/conv.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/cmsis-nn/depthwise_conv.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/cmsis-nn/fully_connected.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/cmsis-nn/mul.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/cmsis-nn/pooling.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/cmsis-nn/softmax.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/cmsis-nn/svdf.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/comparisons.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/concatenation.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/dequantize.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/detection_postprocess.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/elementwise.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/ethosu.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/flexbuffers_generated_data.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/floor.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/hard_swish.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/kernel_runner.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/kernel_util.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/l2norm.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/logical.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/logistic.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/maximum_minimum.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/neg.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/pack.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/pad.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/prelu.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/quantize.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/reduce.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/reshape.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/resize_nearest_neighbor.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/round.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/shape.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/split.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/split_v.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/strided_slice.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/sub.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/tanh.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/unpack.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/memory_helpers.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/memory_planner/greedy_memory_planner.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/memory_planner/linear_memory_planner.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/micro_allocator.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/micro_error_reporter.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/micro_interpreter.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/micro_profiler.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/micro_string.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/micro_utils.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/recording_micro_allocator.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/recording_simple_memory_allocator.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/rp2/debug_log.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/rp2/micro_time.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/simple_memory_allocator.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/test_helpers.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/testing/test_conv_model.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/schema/schema_utils.cpp
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/LICENSE
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/core/public/version.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/c/builtin_op_data.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/c/common.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/core/api/error_reporter.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/core/api/flatbuffer_conversions.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/core/api/op_resolver.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/core/api/profiler.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/core/api/tensor_utils.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/common.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/compatibility.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/cppmath.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/max.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/min.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/optimized/neon_check.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/portable_tensor.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/quantization_util.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/add.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/arg_min_max.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/binary_function.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/ceil.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/comparisons.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/concatenation.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/conv.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/depthwiseconv_float.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/depthwiseconv_uint8.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/dequantize.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/floor.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/fully_connected.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/hard_swish.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/integer_ops/add.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/integer_ops/conv.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/integer_ops/depthwise_conv.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/integer_ops/fully_connected.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/integer_ops/l2normalization.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/integer_ops/logistic.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/integer_ops/mean.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/integer_ops/mul.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/integer_ops/pooling.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/integer_ops/tanh.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/l2normalization.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/logistic.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/maximum_minimum.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/mul.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/neg.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/pad.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/pooling.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/prelu.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/process_broadcast_shapes.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/quantize.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/reduce.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/requantize.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/resize_nearest_neighbor.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/round.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/softmax.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/strided_slice.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/sub.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/reference/tanh.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/strided_slice_logic.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/tensor_ctypes.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/internal/types.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/kernel_util.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/op_macros.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/kernels/padding.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/all_ops_resolver.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/benchmarks/keyword_scrambled_model_data.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/benchmarks/micro_benchmark.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/compatibility.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/debug_log.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/activation_utils.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/ethosu.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/flexbuffers_generated_data.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/fully_connected.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/kernel_runner.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/kernel_util.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/micro_ops.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/kernels/micro_utils.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/memory_helpers.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/memory_planner/greedy_memory_planner.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/memory_planner/linear_memory_planner.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/memory_planner/memory_planner.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/micro_allocator.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/micro_error_reporter.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/micro_interpreter.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/micro_mutable_op_resolver.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/micro_op_resolver.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/micro_profiler.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/micro_string.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/micro_time.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/micro_utils.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/recording_micro_allocator.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/recording_micro_interpreter.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/recording_simple_memory_allocator.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/simple_memory_allocator.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/micro/test_helpers.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/portable_type_to_tflitetype.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/schema/schema_generated.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/schema/schema_utils.h
  ${CMAKE_SOURCE_DIR}/lib/tensorflow/lite/version.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ActivationFunctions/arm_nn_activations_q15.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ActivationFunctions/arm_nn_activations_q7.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ActivationFunctions/arm_relu6_s8.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ActivationFunctions/arm_relu_q15.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ActivationFunctions/arm_relu_q7.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/BasicMathFunctions/arm_elementwise_add_s8.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/BasicMathFunctions/arm_elementwise_mul_s8.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_w.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_x.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_y.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_z.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ConvolutionFunctions/arm_convolve_1_x_n_s8.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ConvolutionFunctions/arm_convolve_1x1_HWC_q7_fast_nonsquare.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ConvolutionFunctions/arm_convolve_1x1_s8_fast.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ConvolutionFunctions/arm_convolve_HWC_q15_basic.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ConvolutionFunctions/arm_convolve_HWC_q15_fast.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ConvolutionFunctions/arm_convolve_HWC_q15_fast_nonsquare.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ConvolutionFunctions/arm_convolve_HWC_q7_RGB.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ConvolutionFunctions/arm_convolve_HWC_q7_basic.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ConvolutionFunctions/arm_convolve_HWC_q7_basic_nonsquare.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ConvolutionFunctions/arm_convolve_HWC_q7_fast.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ConvolutionFunctions/arm_convolve_HWC_q7_fast_nonsquare.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ConvolutionFunctions/arm_convolve_s8.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ConvolutionFunctions/arm_convolve_wrapper_s8.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ConvolutionFunctions/arm_depthwise_conv_3x3_s8.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ConvolutionFunctions/arm_depthwise_conv_s8.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ConvolutionFunctions/arm_depthwise_conv_s8_opt.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ConvolutionFunctions/arm_depthwise_conv_u8_basic_ver1.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ConvolutionFunctions/arm_depthwise_conv_wrapper_s8.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ConvolutionFunctions/arm_depthwise_separable_conv_HWC_q7.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ConvolutionFunctions/arm_depthwise_separable_conv_HWC_q7_nonsquare.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ConvolutionFunctions/arm_nn_depthwise_conv_s8_core.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ConvolutionFunctions/arm_nn_mat_mult_kernel_q7_q15.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ConvolutionFunctions/arm_nn_mat_mult_kernel_q7_q15_reordered.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ConvolutionFunctions/arm_nn_mat_mult_kernel_s8_s16.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ConvolutionFunctions/arm_nn_mat_mult_kernel_s8_s16_reordered.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ConvolutionFunctions/arm_nn_mat_mult_s8.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_mat_q7_vec_q15.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_mat_q7_vec_q15_opt.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q15.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q15_opt.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q7.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q7_opt.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_s8.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/NNSupportFunctions/arm_nn_accumulate_q7_to_q15.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/NNSupportFunctions/arm_nn_add_q7.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/NNSupportFunctions/arm_nn_depthwise_conv_nt_t_padded_s8.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/NNSupportFunctions/arm_nn_depthwise_conv_nt_t_s8.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/NNSupportFunctions/arm_nn_mat_mul_core_1x_s8.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/NNSupportFunctions/arm_nn_mat_mul_core_4x_s8.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/NNSupportFunctions/arm_nn_mat_mult_nt_t_s8.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/NNSupportFunctions/arm_nn_mult_q15.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/NNSupportFunctions/arm_nn_mult_q7.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/NNSupportFunctions/arm_nn_vec_mat_mult_t_s8.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/NNSupportFunctions/arm_nntables.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/NNSupportFunctions/arm_q7_to_q15_no_shift.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/NNSupportFunctions/arm_q7_to_q15_reordered_no_shift.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/NNSupportFunctions/arm_q7_to_q15_reordered_with_offset.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/NNSupportFunctions/arm_q7_to_q15_with_offset.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/PoolingFunctions/arm_avgpool_s8.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/PoolingFunctions/arm_max_pool_s8.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/PoolingFunctions/arm_pool_q7_HWC.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/ReshapeFunctions/arm_reshape_s8.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/SVDFunctions/arm_svdf_s8.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_q15.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_q7.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_u8.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_with_batch_q7.c
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/Core/Include/cmsis_armclang.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/Core/Include/cmsis_compiler.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/Core/Include/cmsis_gcc.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/DSP/Include/arm_common_tables.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/DSP/Include/arm_helium_utils.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/DSP/Include/arm_math.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/DSP/Include/arm_math_memory.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/DSP/Include/arm_math_types.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/DSP/Include/dsp/basic_math_functions.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/DSP/Include/dsp/bayes_functions.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/DSP/Include/dsp/complex_math_functions.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/DSP/Include/dsp/controller_functions.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/DSP/Include/dsp/distance_functions.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/DSP/Include/dsp/fast_math_functions.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/DSP/Include/dsp/filtering_functions.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/DSP/Include/dsp/interpolation_functions.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/DSP/Include/dsp/matrix_functions.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/DSP/Include/dsp/none.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/DSP/Include/dsp/statistics_functions.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/DSP/Include/dsp/support_functions.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/DSP/Include/dsp/svm_defines.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/DSP/Include/dsp/svm_functions.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/DSP/Include/dsp/transform_functions.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/DSP/Include/dsp/utils.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Include/arm_nn_tables.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Include/arm_nn_types.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Include/arm_nnfunctions.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/CMSIS/NN/Include/arm_nnsupportfunctions.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/cmsis/LICENSE.txt
  ${CMAKE_SOURCE_DIR}/lib/third_party/flatbuffers/LICENSE.txt
  ${CMAKE_SOURCE_DIR}/lib/third_party/flatbuffers/include/flatbuffers/base.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/flatbuffers/include/flatbuffers/flatbuffers.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/flatbuffers/include/flatbuffers/flexbuffers.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/flatbuffers/include/flatbuffers/stl_emulation.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/flatbuffers/include/flatbuffers/util.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/gemmlowp/LICENSE
  ${CMAKE_SOURCE_DIR}/lib/third_party/gemmlowp/fixedpoint/fixedpoint.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/gemmlowp/fixedpoint/fixedpoint_neon.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/gemmlowp/fixedpoint/fixedpoint_sse.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/gemmlowp/internal/detect_platform.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/kissfft/COPYING
  ${CMAKE_SOURCE_DIR}/lib/third_party/kissfft/_kiss_fft_guts.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/kissfft/kiss_fft.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/kissfft/tools/kiss_fftr.h
  ${CMAKE_SOURCE_DIR}/lib/third_party/ruy/LICENSE
  ${CMAKE_SOURCE_DIR}/lib/third_party/ruy/ruy/profiler/instrumentation.h
)