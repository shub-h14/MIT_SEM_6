from django.urls import path
from .views import promotion_eligibility_view

urlpatterns = [
    path('', promotion_eligibility_view, name='promotion_eligibility'),
]
