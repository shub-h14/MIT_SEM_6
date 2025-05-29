from django import forms

class PromotionForm(forms.Form):
    employee_id = forms.ChoiceField(choices=[])  # Choices will be set dynamically in view
    date_of_joining = forms.DateField(widget=forms.DateInput(attrs={'type': 'date'}))
