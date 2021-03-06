// Copyright (c) 2020 Run Jump Labs LLC.  All right reserved. 
// This code is licensed under MIT license (see license.txt for details)

#ifndef DM_FX_PITCH_SHIFT_H
#define DM_FX_PITCH_SHIFT_H


/**
 * @brief      Effect: Pitch shifter - shifts audio up or down in pitch
 * 
 * This is a de-glitching, time-domain based implmentation.  Also see the 
 * fx_pitch_shift_fd pitch shifter which provides a frequency-domain based
 * approach (phase vocoder).
 * 
 */
class fx_pitch_shift: public fx_effect {

  private:

    // Ring modulator parameters
    float param_freq_shift;

    // Control nodes
    fx_control_node node_ctrl_freq_shift;

 public:

    /**
     * Audio routing node: primary audio input
     */
    fx_audio_node * input;

    /**
     * Audio routing node: primary audio output
     */
    fx_audio_node * output;


    // Control node names that users will be using
    fx_control_node * freq_shift;

    // Constructor
    fx_pitch_shift(float pitch_shift_freq) : 
        node_ctrl_freq_shift(NODE_IN, NODE_FLOAT, "node_ctrl_freq_shift", this, FX_PITCH_SHIFT_PARAM_ID_FREQ_SHIFT) {
      
      // Set class
      type = FX_PITCH_SHIFT;

      // Set name
      strcpy(effect_name, "pitch shift");

      // Set parameters
      param_freq_shift = pitch_shift_freq;

      // Assign programmable node names
      input = &node_input;
      output = &node_output;

      // Defaults
      param_enabled = true;

      // Initialize parameter stack
      int indx = 1;
      param_stack[indx] = &param_freq_shift;
      param_stack_types[indx++] = T_FLOAT;
      total_params = indx;

      // Add addiitonal notes to the control stack
      control_node_stack[total_control_nodes++] = &node_ctrl_freq_shift;

      freq_shift = &node_ctrl_freq_shift;

    }

    /**
     * @brief      Enable the pitch shifter (it is enabled by default)
     */
    void enable() {
      CHECK_LAST_ENABLED();
      param_enabled = true; 
      parent_canvas->spi_transmit_param(FX_PITCH_SHIFT, instance_id, T_BOOL, FX_PITCH_SHIFT_PARAM_ID_ENABLED, (void *) &param_enabled);
    }

    /**
     * @brief      Bypass the pitch shifter (will just pass clean audio through)
     */
    void bypass() {
      CHECK_LAST_DISABLED();
      param_enabled = false; 
      parent_canvas->spi_transmit_param(FX_PITCH_SHIFT, instance_id, T_BOOL, FX_PITCH_SHIFT_PARAM_ID_ENABLED, (void *) &param_enabled);
    }

    /**
     * @brief      Update the pitch shifter value.  A freq_shift of 0.5 will drop down one octave.  A value of 
     *             2.0 will go up one octave.  A value of 1.0 will play at current pitch (no shift). 
     *
     * @param[in]  freq_shift  The frequency shift
     */
    void set_freq_shift(float freq_shift) { 

      CHECK_LAST(freq_shift, param_freq_shift);

      // If this node is being controlled by a controller, don't allow a direct write to it
      if (node_ctrl_freq_shift.connected) {
        return;
      }

      param_freq_shift = freq_shift;
      parent_canvas->spi_transmit_param(FX_PITCH_SHIFT, instance_id, T_FLOAT, FX_PITCH_SHIFT_PARAM_ID_FREQ_SHIFT, (void *) &param_freq_shift);
    }


    /**
     * @brief      Print the parameters for this effect
     */
    void  print_params(void) {
      char buf[64];
      const char * num;
      String val;

      sprintf(buf," Enabled: %s", param_enabled ? "true" : "false");  Serial.println(buf);
      sprintf(buf," Freq shift ratio: %.2f", param_freq_shift);  Serial.println(buf);

      Serial.println(" Routing:");
      
      Serial.print("  + node_ctrl_freq_shift: ");
      if (node_ctrl_freq_shift.connected) {
        Serial.println("routed");
      } else {
        Serial.println("not routed");
      }

      Serial.print("  * node_input: ");      
      if (node_input.connected) {
        Serial.println("routed");
      } else {
        Serial.println("not routed");
      }  

      Serial.print("  * node_output: ");      
      if (node_output.connected) {
        Serial.println("routed");
      } else {
        Serial.println("not routed");
      }  

      Serial.println();
    }
};

#endif 	// DM_FX_PITCH_SHIFT_H
