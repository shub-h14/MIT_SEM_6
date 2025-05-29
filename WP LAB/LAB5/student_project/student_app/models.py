from django.db import models

# Create your models here.

class Student(models.Model):
    name = models.CharField(max_length=100)
    dob = models.DateField()
    address = models.TextField()
    contact = models.CharField(max_length=15)
    email = models.EmailField()
    english = models.FloatField()
    physics = models.FloatField()
    chemistry = models.FloatField()
