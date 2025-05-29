# Create your views here.
from django.shortcuts import render
from datetime import date
from .forms import PromotionForm

EMPLOYEE_IDS = [('E001', 'E001'), ('E002', 'E002'), ('E003', 'E003'), ('E004', 'E004')]

def promotion_eligibility_view(request):
    message = ''
    if request.method == 'POST':
        form = PromotionForm(request.POST)
        form.fields['employee_id'].choices = EMPLOYEE_IDS
        if form.is_valid():
            doj = form.cleaned_data['date_of_joining']
            today = date.today()
            experience_years = (today - doj).days / 365.25
            message = "YES" if experience_years > 5 else "NO"
    else:
        form = PromotionForm()
        form.fields['employee_id'].choices = EMPLOYEE_IDS

    return render(request, 'employee_app/promotion_form.html', {'form': form, 'message': message})
