from django import forms

class StudentForm(forms.Form):
    name = forms.CharField(max_length=100)
    dob = forms.DateField(widget=forms.DateInput(attrs={'type': 'date'}))
    address = forms.CharField(widget=forms.Textarea)
    contact = forms.CharField(max_length=15)
    email = forms.EmailField()
    english = forms.FloatField()
    physics = forms.FloatField()
    chemistry = forms.FloatField()
