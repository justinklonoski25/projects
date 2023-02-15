# Importing necessary libraries
import numpy as np

# Discounted Cash Flow model function
def dcf_model(cash_flows, discount_rate):
    """
    Calculates the present value of cash flows using the Discounted Cash Flow (DCF) model.
    cash_flows: List of future cash flows
    discount_rate: Discount rate to use in the model
    """
    npv = np.npv(discount_rate, cash_flows) # Calculate net present value
    return npv

# Example usage of the dcf_model function
cash_flows = [100, 150, 200, 250, 300] # Future cash flows
discount_rate = 0.1 # Discount rate of 10%
present_value = dcf_model(cash_flows, discount_rate)

# Output the results
print(f"Future cash flows: {cash_flows}")
print(f"Discount rate: {discount_rate}")
print(f"Present value: {present_value}")
